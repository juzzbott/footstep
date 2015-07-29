#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <QGraphicsView>
#include <QWidget>
#include <QPointer>

#include "mapscene.h"
#include "core/geopoint.h"

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
    //MapView::DragMode dragMode() const;
    //void setDragMode(MapView::DragMode);

    MapScene *scene() const;
    void setScene(MapScene *scene);

    quint8 zoomLevel() const;
    void setZoomLevel(quint8 zoom, ZoomMode mode = CenterZoom);
    void zoomIn(ZoomMode mode = CenterZoom);
    void zoomOut(ZoomMode mode = CenterZoom);

private:
    quint8 _zoomLevel;

    QPointer<QGraphicsView> _childView;

    QPointer<MapScene> _scene;
    QPointer<QGraphicsScene> _childScene;

signals:
    void zoomLevelChanged(quint8 zoom);

public slots:
};

#endif // MAPVIEW_H
