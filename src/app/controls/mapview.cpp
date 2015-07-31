#include <QCoreApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QWidget>
#include <QWheelEvent>
#include <QtDebug>
#include <QThread>

#include "mapview.h"
#include "tilesources/maptilesource.h"
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

MapView::~MapView() {

    qDebug() << this << "Destructing map view";

    // Clear all the tile objects

    // Clear the tile source
    if (!_tileSource.isNull()) {

        // Get the thread of the tile source
        QPointer<QThread> tileSourceThread = _tileSource->thread();

        /*
         Clear the QSharedPointer to the tilesource. Unless there's a serious problem, we should be the
         last thing holding that reference and we expect it to be deleted
        */
        _tileSource.clear();

        // After the tilesource is cleared, we wait for the thread it was running to shut down
        int count = 0;
        const int maxCount = 100;
        while (!tileSourceThread.isNull() && !tileSourceThread->wait(100)) {
            //We have to process events while it's shutting down in case it uses signals/slots to shut down
            //Hint: it does
            QCoreApplication::processEvents(QEventLoop::ExcludeSocketNotifiers | QEventLoop::ExcludeUserInputEvents);
            if (++count == maxCount) {
                return;
            }
        }

    }
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
// Tile Source
//
QSharedPointer<MapTileSource>  MapView::tileSource() const {
    return _tileSource;
}

void MapView::setTileSource(QSharedPointer<MapTileSource> tileSource) {

    // Set the tile source
    _tileSource = tileSource;

    if (!tileSource.isNull()) {

        // Create a new thread just for the new tile source
        QThread *tileSourceThread = new QThread();
        tileSourceThread->start();
        _tileSource->moveToThread(tileSourceThread);

        // Connect so that the thread is destroyed when the tile source is.
        connect(_tileSource.data(),
                SIGNAL(destroyed()),
                tileSourceThread,
                SLOT(quit()));

        connect(tileSourceThread,
                SIGNAL(finished()),
                tileSourceThread,
                SLOT(deleteLater()));

    }

    // Update the MapGrahicsObject
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
