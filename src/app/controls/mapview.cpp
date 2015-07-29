#include <QGraphicsView>
#include <QGraphicsScene>
#include <QWidget>

#include "mapview.h"
#include "internal/internalgraphicsscene.h"

MapView::MapView(MapScene *scene, QWidget *parent) : QGraphicsView(parent)
{

    // Set the scene for the map view.
    this->setScene(scene);
    _zoomLevel = 2;

    // Set drag mode



}

//
// MapScene methods and implementations

MapScene *MapView::scene() const {
    return _scene;
}

void MapView::setScene(MapScene *scene) {

    InternalGraphicsScene *childScene = new InternalGraphicsScene(scene, this);

    //The QGraphicsScene needs to know when our zoom level changes so it can notify objects
    connect(this, SIGNAL(zoomLevelChanged(quint8)), childScene, SLOT(handleZoomLevelChanged()));

}

//
// Zoom methods and implementations

quint8 MapView::zoomLevel() const {
    return _zoomLevel;
}

void MapView::zoomIn(ZoomMode mode) {
    this->setZoomLevel(this->zoomLevel() + 1, mode);
}

void MapView::zoomOut(ZoomMode mode) {
    this->setZoomLevel(this->zoomLevel() - 1, mode);
}

void MapView::setZoomLevel(quint8 zoom, ZoomMode mode) {

    // Ensure the zoom level is not the current
    if (zoom == _zoomLevel) {
        return;
    }

    // Set the new zoom level
    _zoomLevel = zoom;

}
