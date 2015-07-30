#ifndef MAPTILESOURCE_H
#define MAPTILESOURCE_H

#include <QCache>
#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QImage>
#include <QMutex>
#include <QObject>
#include <QHash>

class MapTileSource : public QObject
{
    Q_OBJECT

    /**
     * @brief Determines how the map source tiles will be cached, if at all.
     */
    enum CacheMode {
        NoCaching,
        DiskAndMemoryCache
    };


public:
    explicit MapTileSource();
    virtual ~MapTileSource();

    /**
     * @brief Causes the MapTileSource to request the map tile at x,y for zoom level z.
     * When complete, the tileRetrieved signal will be emitted and can be used by the getFinishedTile() method.
     * @param x
     * @param y
     * @param zoom
     */
    void requestTile(quint32 x, quint32 y, quint8 zoom);

    /**
     * @brief Returns a pointer to the retrieved image tile. The requestTile() method must be called initially
     * and then wait for the tileRetrieved signal before calling this method.
     * The caller must delete the QImage pointer. Null returned if request failure.
     * @param x
     * @param zoom
     * @return
     */
    QImage *getFinishedTile(quint32 x, quint32 y, quint8 zoom);

    MapTileSource::CacheMode cacheMode() const;
    void setCacheMode(MapTileSource::CacheMode);

    /**
     * @brief Returns the name of the map tile source. An implementation of the MapTileSource class must implement this method.
     * @return QString The name of the map tile source.
     */
    virtual QString name() const = 0;

    /**
     * @brief Returns the extention of the tile file. The extension should not include the "." eg: "png" instead of ".png".
     * An implementation of the MapTileSource class must implement this method.
     * @return QString The tile file extension
     */
    virtual QString tileFileExtension() const = 0;

signals:

    /**
     * @brief Signal is emitted when a tile that has been requested with the requestTile method is returned.
     * The getFinishedTile() method can be called to use the retrieved file.
     * @param x
     * @param y
     * @param zoom
     */
    void tileRetrieved(quint32 x, quint32 y, quint8 zoom);

    /**
     * @brief Signal is emitted when the requestTile method is called.
     * @param x
     * @param y
     * @param zoom
     */
    void tileRequested(quint32 x, quint32 y, quint8 zoom);

    /**
     * @brief Emitted when the tile source properties have changed and the map tiles should be refreshed.
     */
    void allTileInvalidated();

public slots:

private slots:

    /**
     * @brief Starts the request to fetch the tile from the map server.
     * @param x
     * @param y
     * @param zoom
     */
    void startTileRequest(quint32 x, quint32 y, quint8 zoom);

    /**
     * @brief Clears the temporary cache hash.
     */
    void clearTempCache();

protected:

    /**
     * @brief Generates a cache id to be used for tiles based on the x, y coordinates and zoom level.
     * @param x the x-coord of the tile.
     * @param y the y-coord of the tile.
     * @param zoom the zoom level of the tile.
     * @return The string cacheKey.
     */
    static QString createCacheKey(quint32 x, quint32 y, quint8 zoom);

    /**
     * @brief Retrieves the x,y coordinates and zoom level from the cacheKey and puts the values into the variables
     * pointed to by x, y and zoom.
     * Returns true on success, false on failure.
     * @param cacheKey The cache Id to get the values from.
     * @param x The pointer to the x value.
     * @param y The pointer to the y value.
     * @param zoom The pointer to the zoom value.
     * @return True on success, otherwise false.
     */
    static bool cacheKeyToXYZ(const QString &cacheKey, quint32 *x, quint32 *y, quint8 *zoom);

    /**
     * @brief Retrieves a QImage object from the memory cache based on the cacheKey. Returns a point to the image on success,
     * null on failure. Caller is responsible for deleting the QImage.
     * @param cacheKey The key for the cache item.
     * @return Pointer to the QImage object, or null on failure.
     */
    QImage *fromMemCache(const QString &cacheKey);

    /**
     * @brief Adds the pointer to the QImage to the memory cache using the cacheKey.
     * @param cacheKey The key for the cache item.
     * @param image The pointer to the QImage item to store in the cache.
     * @param expires The date and time the cache item expires.
     */
    void toMemCache(const QString &cacheKey, QImage *image, const QDateTime &expires = QDateTime());

    /**
     * @brief Retrieves a QImage object from the disk cache based on the cacheKey. Returns a point to the image on success,
     * null on failure. Caller is responsible for deleting the QImage.
     * @param cacheKey The key for the cache item.
     * @return Pointer to the QImage object, or null on failure.
     */
    QImage *fromDiskCache(const QString &cacheKey);

    /**
     * @brief Saves the pointer to the QImage to the disk cache using the cacheKey.
     * @param cacheKey The key for the cache item.
     * @param image The pointer to the QImage item to store in the cache.
     * @param expires The date and time the cache item expires.
     */
    void toDiskCache(const QString &cacheKey, QImage *image, const QDateTime &expires = QDateTime());

    /**
     * @brief Returns the date time that the tile is supposed to be removed from any cache.
     * This should only be called for images currently in a cache.
     * @param cacheKey The cache key to check the expiration for.
     * @return THe QDateTime that the tile should be considered expired.
     */
    QDateTime getTileExpirationTime(const QString &cacheKey);

    /**
     * @brief Sets the date and time when the tile is supposed to expire from the cache.
     * @param cacheKey of the tile.
     * @param expireTime The date and time time the cache is to be expired.
     */
    void setTileExpirationTime(const QString &cacheKey, QDateTime expireTime);

    /**
     * @brief The fetch tile method goes off to the actual map source provider and fetches the file at x,y for zoom level zoom.
     * Once the file is retrieved, if cache is enabled, it's added to the cache.
     * When successful, this method should just call prepareRetrievedFile. On failure, do nothing.
     * @param x
     * @param y
     * @param zoom
     */
    virtual void fetchTile(quint32 x, quint32 y, quint8 zoom) = 0;

    /**
     * @brief Is called only tiles which were newly generated or newly aquired from the server i.e. not cached.
     * @param x
     * @param y
     * @param zoom
     * @param image
     * @param expireTime
     */
    void prepareNewlyRetrievedTile(quint32 x, quint32 y, quint8 zoom, QImage *image, QDateTime expireTime = QDateTime());

private:

    /**
     * @brief prepareRetrievedTile prepares a generated/retrieve tile for retrieval by the client
     * and notifies the client that the tile is ready.
     * @param x
     * @param y
     * @param zoom
     * @param image
     */
    void prepareRetrievedTile(quint32 x, quint32 y, quint8 zoom, QImage *image);

    /**
     * @brief Gets the directory that stores the cached image based on the x,y & zoom values.
     * @param x
     * @param zoom
     * @return
     */
    QDir getDiskCacheDirectory(quint32 x, quint8 zoom) const;

    /**
     * @brief Gets the full path to the tile image on the disk cache.
     * @param x
     * @param y
     * @param zoom
     * @return Full path to the disk cache image file.
     */
    QString getDiskCacheFilePath(quint32 x, quint32 y, quint8 zoom) const;

    /**
     * @brief Loads the cache expiration file into memory.
     */
    void loadCacheExpirationsFile();

    /**
     * @brief Saves the cache expiration file to disk.
     */
    void saveCacheExpirationsFile();

    /**
     * @brief Gets the directory that stores the cache expirations file.
     * @return
     */
    QDir getCacheExpirationsDirectory() const;

    bool _cacheExpirationsLoaded;
    QString _cacheExpirationsFile;

    MapTileSource::CacheMode _cacheMode;
    bool _cacheExpirationLoaded;

    // Temporary cache to store retrieved files from.
    QCache<QString, QImage> _tempCache;
    QMutex _tempCacheLock;

    // Actual cache to store image tiles in memory.
    QCache<QString, QImage> _memoryCache;
    QHash<QString, QDateTime> _cacheExpirations;
};

#endif // MAPTILESOURCE_H
