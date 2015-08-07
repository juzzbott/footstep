#ifndef MAPGRAPHICSOBJECT_H
#define MAPGRAPHICSOBJECT_H

#include <QObject>
#include <QPointF>

#include "controls/internal/internalgraphicsobject.h"

class MapGraphicsObject : public QObject
{
    Q_OBJECT

public:
    enum MapGraphicsObjectFlag {
        ObjectIsMovable = 0x01,
        ObjectIsSelectable = 0x02,
        ObjectIsFocusable = 0x04,
    };
    Q_DECLARE_FLAGS(MapGraphicsObjectFlags,MapGraphicsObjectFlag)

    //InternalGraphicsObject will call some of our protected event handlers that nobody else needs to touch
    friend class InternalGraphicsObject;

public:
    explicit MapGraphicsObject(bool sizeIsZoomInvariant = false, QObject *parent = 0);
    virtual ~MapGraphicsObject();

    bool sizeIsZoomInvariant() const;

signals:

public slots:

private:
    bool _sizeIsZoomInvariant;

    bool _enabled;
    double _opacity;
    bool _visible;

    MapGraphicsObject *_parent;

    QPointF _position;
    double _rotation;
    double _zValue;
    bool _selected;

    QString _toolTip;

    MapGraphicsObject::MapGraphicsObjectFlag _flags;

    bool _constructed;
};
Q_DECLARE_OPERATORS_FOR_FLAGS(MapGraphicsObject::MapGraphicsObjectFlags)

#endif // MAPGRAPHICSOBJECT_H
