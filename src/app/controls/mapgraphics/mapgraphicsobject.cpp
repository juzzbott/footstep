#include "mapgraphicsobject.h"

#include <QtDebug>
#include <QKeyEvent>
#include <QTimer>

MapGraphicsObject::MapGraphicsObject(bool sizeIsZoomInvariant, QObject *parent) : QObject(parent)
{

    _sizeIsZoomInvariant = sizeIsZoomInvariant;
    _opacity = 1.0;
    _position = QRectF(0.0, 0.0);
    _rotation = 0.0;
    _visible = true;
    _zValue = 0.0;
    _selected = true;

}

MapGraphicsObject::~MapGraphicsObject() {
}

//
// Size is zoom invariant
//
bool MapGraphicsObject::sizeIsZoomInvariant() const {
    return _sizeIsZoomInvariant;
}

//
// Enabled
//

