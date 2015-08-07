#include "internalgraphicsobject.h"

#include <QKeyEvent>
#include <QtDebug>

InternalGraphicsObject::InternalGraphicsObject(MapGraphicsObject *mgObj, QGraphicsItem *parent) : QGraphicsObject(parent) {

    // Set the map graphics object
    this->setMapGraphicsObj(mgObj);
    this->setZValue(5.0);

    this->setFlag(QGraphicsItem::ItemSendsScenePositionChanges, true);

}

InternalGraphicsObject::~InternalGraphicsObject() {
}

//
// Bounding rect.
//

//
// Set Selected
//
InternalGraphicsObject::setSelected(bool selected) {

    QGraphicsItem::setSelected(selected);

    // Set the selected flag on the map graphics object
    //_mapGraphicsObj->set

}

//
// Set Map Graphics Object.
//
void InternalGraphicsObject::setMapGraphicsObj(MapGraphicsObject *mapGraphicsObj) {

    _mapGraphicsObj = mapGraphicsObj;

    // Ensure the map graphics object is valid
    if (_mapGraphicsObj == 0) {
        return;
    }

    // Get all the info about the map graphics obj.

}
