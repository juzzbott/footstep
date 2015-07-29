#include <QGraphicsView>
#include <QGraphicsScene>
#include <QWidget>
#include <QWheelEvent>

#include "mapview.h"
#include "internal/internalgraphicsscene.h"
#include "internal/internalgraphicsview.h"

MapView::MapView(MapScene *scene, QWidget *parent) : QGraphicsView(parent)
{

    // Set the scene for the map view.
    this->setScene(scene);
    _zoomLevel = 2;

    // Set the default drag mode
    this->setDragMode(MapView::ScrollHandDrag);


}

//
// MapScene methods and implementations
//

MapScene *MapView::scene() const {
    return _scene;
}

void MapView::setScene(MapScene *scene) {

    // Create the child scene.
    InternalGraphicsScene *childScene = new InternalGraphicsScene(scene, this);

    //The QGraphicsScene needs to know when our zoom level changes so it can notify objects
    connect(this, SIGNAL(zoomLevelChanged(quint8)), childScene, SLOT(handleZoomLevelChanged()));

    // Create the child view that will handle the drawing for us.
    InternalGraphicsView *childView = new InternalGraphicsView(childScene, this);

    connect(childView, SIGNAL(hadWheelEvent(QWheelEvent*)), this, SLOT(handleChildViewScrollWheel(QWheelEvent*)));
}

//
// Drag Mode
//

MapView::DragMode MapView::dragMode() const {
    return _dragMode;
}

void MapView::setDragMode(MapView::DragMode mode) {

    // Set the drag mode
    _dragMode = mode;

    // Get the drag mode for the child view
    QGraphicsView::DragMode childViewDragMode;
    if (_dragMode == MapView::ScrollHandDrag) {
        childViewDragMode = QGraphicsView::ScrollHandDrag;
    } else if (_dragMode == MapView::RubberBandDrag) {
        childViewDragMode = QGraphicsView::RubberBandDrag;
    } else {
        childViewDragMode = QGraphicsView::NoDrag;
    }

    // Set the child view drag mode if it's not null
    if (_childView.isNull()) {
        return;
    }

    _childView->setDragMode(childViewDragMode);

}

//
// Zoom methods and implementations
//

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

//
// SLOTS
//

void MapView::handleChildViewScrollWheel(QWheelEvent *event) {

    event->setAccepted(true);

    // Handle the zoom functionality on the map view
    this->setDragMode(MapView::ScrollHandDrag);
    if (event->delta() > 0) {
        this->zoomIn(MapView::MouseZoom);
    } else {
        this->zoomOut(MapView::MouseZoom);
    }
}
