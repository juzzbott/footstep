#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <QGraphicsView>
#include <QWidget>
#include <QPointer>
#include <QSharedPointer>

#include "mapscene.h"
#include "core/geopoint.h"
#include "tilesources/maptilesource.h"

class MapView : public QGraphicsView
{
    Q_OBJECT

public:
    enum DragMode {
        NoDrag,
        ScrollHandDrag,
        RubberBandDrag
    };

    enum ZoomMode {
        CenterZoom,
        MouseZoom
    };

public:
    explicit MapView(MapScene *scene, QWidget *parent = 0);
    //virtual ~MapView();
    //
    //GeoPoint center() const;
    //void centerOn(const GeoPoint& pos);
    //void centerOn(double lat, double lon);
    //void centerOn(const QObject *obj);
    //
    //GeoPoint mapToScene(const QPoint viewPos) const;
    //
    MapView::DragMode dragMode() const;
    void setDragMode(MapView::DragMode);

    MapScene *scene() const;
    void setScene(MapScene *scene);

    quint8 zoomLevel() const;
    void setZoomLevel(quint8 zoom, ZoomMode mode = CenterZoom);
    void zoomIn(ZoomMode mode = CenterZoom);
    void zoomOut(ZoomMode mode = CenterZoom);

    /**
     * @brief Gets the map tile source.
     * @return
     */
    QSharedPointer<MapTileSource> tileSource() const;

    /**
     * @brief Sets the tile source for the map view.
     * @param tileSource
     */
    void setTileSource(QSharedPointer<MapTileSource> tileSource);

signals:
    void zoomLevelChanged(quint8 zoom);

protected slots:
    virtual void handleChildViewScrollWheel(QWheelEvent *event);

private:
    quint8 _zoomLevel;
    DragMode _dragMode;

    QPointer<QGraphicsView> _childView;

    QPointer<MapScene> _scene;
    QPointer<QGraphicsScene> _childScene;

    QSharedPointer<MapTileSource> _tileSource;

};

#endif // MAPVIEW_H
