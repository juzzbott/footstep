#include <QCache>
#include <QDataStream>
#include <QDir>
#include <QImage>
#include <QMutexLocker>
#include <QString>
#include <QStringList>
#include <QStringBuilder>
#include <QtDebug>

#include "maptilesource.h"

const QString CACHE_DIRECTORY_NAME = ".map_cache";
const quint32 DEFAULT_CACHE_DAYS = 7;
const quint32 MAX_DISK_CACHE_READ_ATTEMPTS = 100000;

MapTileSource::MapTileSource() : QObject(), _cacheExpirationLoaded(false)
{

    // Sets the cache mode for the control
    this->setCacheMode(MapTileSource::DiskAndMemoryCache);

    connect(this,
            SIGNAL(tileRequested(quint32,quint32,quint8)),
            this,
            SLOT(startTileRequest(quint32,quint32,quint8)),
            Qt::QueuedConnection);

    connect(this,
            SIGNAL(allTileInvalidated()),
            this,
            SLOT(clearTempCache()));

}

MapTileSource::~MapTileSource() {
    this->saveCacheExpirationsFile();
}

//
// Request and retrieve tile methods.
//
void MapTileSource::requestTile(quint32 x, quint32 y, quint8 zoom) {

    // We emit the tileRequested signal to help with cross threads.
    this->tileRequested(x, y, zoom);

}

QImage *MapTileSource::getFinishedTile(quint32 x, quint32 y, quint8 zoom) {

    // Create the cache id
    const QString cacheKey = MapTileSource::createCacheKey(x, y, zoom);

    // Lock the temp cache
    QMutexLocker lock(&_tempCacheLock);

    // Ensure the item exists in the temp cache
    if (!_tempCache.contains(cacheKey)) {
        qWarning() << "getFinishedTile() called but there is no file in the cache.";
        return 0;
    }

    return _tempCache.take(cacheKey);

}

//
// Cache mode
//
MapTileSource::CacheMode MapTileSource::cacheMode() const {
    return _cacheMode;
}

void MapTileSource::setCacheMode(MapTileSource::CacheMode mode) {
    _cacheMode = mode;
}

//
// Cache helpers
//
QString MapTileSource::createCacheKey(quint32 x, quint32 y, quint8 zoom) {

    QString cacheKey = QString::number(x) % "_" % QString::number(y) % "_" % QString::number(zoom);
    return cacheKey;

}

bool MapTileSource::cacheKeyToXYZ(const QString &cacheKey, quint32 *x, quint32 *y, quint8 *zoom) {

    // Split and validate the cacheKey into parts
    QStringList cacheKeyParts = cacheKey.split('_');
    if (cacheKeyParts.size() != 3) {
        qWarning() << "Invalid cacheKey: " << cacheKey << ". Cannot convert to x,y,zoom.";
        return false;
    }

    // Set the result flag
    bool result = true;

    // convert the values from the string list into the integer vals.
    *x = cacheKeyParts.at(0).toUInt(&result);
    if (!result) {
        return false;
    }

    *y = cacheKeyParts.at(1).toUInt(&result);
    if (!result) {
        return false;
    }

    *zoom = cacheKeyParts.at(2).toUInt(&result);
    if (!result) {
        return false;
    }

    // return the result
    return result;

}

//
// Memory Cache
//
QImage *MapTileSource::fromMemCache(const QString &cacheKey) {

    // Create the pointer to store the image in
    QImage *fromCache = 0;

    if (_memoryCache.contains(cacheKey)) {

        // Determine when the cached item was meant to expire
        QDateTime expireTime = this->getTileExpirationTime(cacheKey);

        // If the tile has expired, remove from the cache
        if (QDateTime::currentDateTimeUtc().secsTo(expireTime) <= 0) {
            _memoryCache.remove(cacheKey);
        } else {

            // Cache item is still valid, so return it.
            fromCache = new QImage(*_memoryCache.object(cacheKey));
        }

    }

    // return the image from cache
    return fromCache;

}

void MapTileSource::toMemCache(const QString &cacheKey, QImage *image, const QDateTime &expires) {

    // Ensure we have an object to cache
    if (image == 0) {
        return;
    }

    // If the cache item already exists, just return
    if (_memoryCache.contains(cacheKey)) {
        return;
    }

    // Set the expiry time
    this->setTileExpirationTime(cacheKey, expires);

    // Make a copy of the image and add to the cache
    QImage *copy = new QImage(*image);
    _memoryCache.insert(cacheKey, copy);

}

//
// Disk cache
//
QImage *MapTileSource::fromDiskCache(const QString &cacheKey) {

    // Get the x, y and zoom from the cacheKey
    quint32 x, y;
    quint8 zoom;

    // Get the values based on the cache key
    if (!MapTileSource::cacheKeyToXYZ(cacheKey, &x, &y, &zoom)) {
        return 0;
    }

    // Get the path to the disk cache file and check if the file exists in the disk cache
    const QString path = this->getDiskCacheFilePath(x, y, zoom);
    QFile fp(path);
    if (!fp.exists()) {
        return 0;
    }

    // Determine when the file was due to expire.
    QDateTime expireTime = this->getTileExpirationTime(cacheKey);

    // If the cache expireTime has past, then remove from the disk
    if (QDateTime::currentDateTimeUtc().secsTo(expireTime) <= 0) {
        if (!QFile::remove(path)) {
            qWarning() << "Failed to delete old cached file: " << path;
        }
        return 0;
    }

    // If we can't open the image for reading, return 0
    if (!fp.open(QFile::ReadOnly)) {
        qWarning() << "Failed to open " << QFileInfo(fp.fileName()).baseName() << " from cache.";
        return 0;
    }

    QByteArray data;
    quint64 counter = 0;
    while (data.length() < fp.size()) {
        data += fp.read(20480);
        if (++counter >= MAX_DISK_CACHE_READ_ATTEMPTS) {
            qWarning() << "Reading cache file " << fp.fileName() << " took too long. Aborting.";
            return 0;
        }
    }

    QImage *image = new QImage();
    if (!image->loadFromData(data)) {
        delete image;
        return 0;
    }

    // return the image
    return image;

}

void MapTileSource::toDiskCache(const QString &cacheKey, QImage *image, const QDateTime &expires) {

    // Get the x, y and zoom from the cacheKey
    quint32 x, y;
    quint8 zoom;

    // Get the values based on the cache key
    if (!MapTileSource::cacheKeyToXYZ(cacheKey, &x, &y, &zoom)) {
        return;
    }

    // Determine what is to be cached
    const QString filePath = this->getDiskCacheFilePath(x, y, zoom);

    // If it's already cached, don't recache it
    QFile fp(filePath);
    if (fp.exists()) {
        return;
    }

    // Set the cache expiration time
    this->setTileExpirationTime(cacheKey, expires);

    // Auto-detect the file format
    const char *format = 0;

    // No compression
    const int quality = 100;

    // Write the image to disk
    if (!image->save(filePath, format, quality)) {
        qWarning() << "Failed to put" << this->name() << x << y << zoom << "into disk cache";
    }

}

QDir MapTileSource::getDiskCacheDirectory(quint32 x, quint8 zoom) const {

    // Build the path to the cache directory
    QString diskCachePath = QDir::homePath() % "/" % CACHE_DIRECTORY_NAME % "/" % this->name() % "/" % QString::number(zoom) % "/" % QString::number(x);

    // Get the directory. If it doesn't exist, create it
    QDir directory = QDir(diskCachePath);
    if (!directory.exists()) {
        if (!directory.mkpath(directory.absolutePath())) {
            qWarning() << "Failed to create cache directory: " << diskCachePath;
        }
    }

    // return the cache path
    return directory;
}

QString MapTileSource::getDiskCacheFilePath(quint32 x, quint32 y, quint8 zoom) const {

    QDir directory = this->getDiskCacheDirectory(x, zoom);
    QString filePath = directory.absolutePath() % "/" % QString::number(y) % "." % this->tileFileExtension();

    return filePath;

}

//
// Cache Expiry methods
//

QDateTime MapTileSource::getTileExpirationTime(const QString &cacheKey) {

    // Load the cache expirations file
    this->loadCacheExpirationsFile();

    // Get the expiry time
    QDateTime expireTime;
    if (_cacheExpirations.contains(cacheKey)) {
        expireTime = _cacheExpirations.value(cacheKey);
    } else {
        qWarning() << "Tile " << cacheKey << " has unknown expiry time. Resetting to default of " << DEFAULT_CACHE_DAYS << " days.";
        expireTime = QDateTime::currentDateTimeUtc().addDays(DEFAULT_CACHE_DAYS);
        _cacheExpirations.insert(cacheKey, expireTime);
    }

    // return the expire time
    return expireTime;

}

void MapTileSource::setTileExpirationTime(const QString &cacheKey, QDateTime expireTime) {

    // Ensure the cache expirations file is loaded
    this->loadCacheExpirationsFile();

    // Ensure the expire time is valid. If not, reset to default
    if (expireTime.isNull()) {
        expireTime = QDateTime::currentDateTimeUtc().addDays(DEFAULT_CACHE_DAYS);
    }

    _cacheExpirations.insert(cacheKey, expireTime);

}

void MapTileSource::loadCacheExpirationsFile() {

    if (_cacheExpirationLoaded) {
        return;
    }

    // If we try and fail, don't attempt again
    _cacheExpirationLoaded = true;

    // Get the cache expirations file path
    QDir cacheDir = this->getCacheExpirationsDirectory();
    QString path = cacheDir.absolutePath() % "/" % "cache_expirations.db";
    _cacheExpirationsFile = path;

    // Ensure the file exists
    QFile fp(path);
    if (!fp.exists()) {
        return;
    }

    // Ensure the file can be open
    if (!fp.open(QIODevice::ReadOnly)) {
        qWarning() << "Failed to open the cache expirations file for reading: " << fp.errorString();
    }

    QDataStream stream(&fp);
    stream >> _cacheExpirations;

}

void MapTileSource::saveCacheExpirationsFile() {

    // If the file is not loaded or the cache expirations is null, then return
    if (!_cacheExpirationLoaded || _cacheExpirations.empty()) {
        return;
    }

    // Create the file
    QFile fp(_cacheExpirationsFile);

    // Ensure the file can be opened for writing
    if (!fp.open(QIODevice::Truncate | QIODevice::WriteOnly)) {
        qWarning() << "Failed to open cache expiration file for writing: " << fp.errorString();
        return;
    }

    // Write the file to disk
    QDataStream stream(&fp);
    stream << _cacheExpirations;
    qDebug() << "Cache expirations file saved to: " << _cacheExpirationsFile;

}

QDir MapTileSource::getCacheExpirationsDirectory() const {

    // Build the path to the cache directory
    QString cacheExpirationsPath = QDir::homePath() % "/" % CACHE_DIRECTORY_NAME % "/" % this->name();

    // Get the directory. If it doesn't exist, create it
    QDir directory = QDir(cacheExpirationsPath);
    if (!directory.exists()) {
        if (!directory.mkpath(directory.absolutePath())) {
            qWarning() << "Failed to create expirations cache directory: " << cacheExpirationsPath;
        }
    }

    // return the cache path
    return directory;

}

//
// Prepare retreieved file
//

void MapTileSource::prepareRetrievedTile(quint32 x, quint32 y, quint8 zoom, QImage *image) {

    // Ensure the image is valid
    if (image == 0) {
        return;
    }

    // Put the image into the temporary cache so that the user can retrieve it.
    QMutexLocker lock(&_tempCacheLock);
    _tempCache.insert(MapTileSource::createCacheKey(x, y, zoom), image);

    // Ensure that we explicitly unlock the mutex lock
    lock.unlock();

    // Emit the signal to let the user know it's ready to call getFinishedTile();
    this->tileRetrieved(x, y, zoom);

}

void MapTileSource::prepareNewlyRetrievedTile(quint32 x, quint32 y, quint8 zoom, QImage *image, QDateTime expireTime) {

    // Insert into caches if enabled
    const QString cacheKey = MapTileSource::createCacheKey(x, y, zoom);
    if (this->cacheMode() == MapTileSource::DiskAndMemoryCache) {
        this->toMemCache(cacheKey, image, expireTime);
        this->toDiskCache(cacheKey, image, expireTime);
    }

    // Put the tile in a client accessable place and notify them that it's ready
    this->prepareRetrievedTile(x, y, zoom, image);
}

//
// Private slots
//

void MapTileSource::startTileRequest(quint32 x, quint32 y, quint8 zoom) {

    // Checks the cache for the image first.
    if (this->cacheMode() == MapTileSource::DiskAndMemoryCache) {

        // Get the cache key and try and load the image from the memory cache
        const QString cacheKey = MapTileSource::createCacheKey(x, y, zoom);
        QImage *cachedImage = this->fromMemCache(cacheKey);

        // If nothing in memory cache, load from disk
        if (!cachedImage) {
            cachedImage = this->fromMemCache(cacheKey);
        }

        // If we got a cache from either of the caches, then prepare it for use by user.
        if (cachedImage) {
            this->prepareRetrievedTile(x, y, zoom, cachedImage);
            return;
        }

    }

    // No image in the cache so fetch from the map server
    this->fetchTile(x, y, zoom);

}

void MapTileSource::clearTempCache() {
    _tempCache.clear();
}
