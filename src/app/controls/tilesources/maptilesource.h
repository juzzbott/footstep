#ifndef MAPTILESOURCE_H
#define MAPTILESOURCE_H

#include <QObject>

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
    QImage *getFinishedTile(quint32 x, quint32, y, quint8 zoom);

    MapTileSource::CacheMode cacheMode() const;
    void setCacheMode(MapTileSource::CacheMode);



signals:

public slots:
};

#endif // MAPTILESOURCE_H
