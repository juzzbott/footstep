#ifndef MAPGRAPHICSOBJECT_H
#define MAPGRAPHICSOBJECT_H

#include <QObject>
#include <QPointF>

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

public:
    explicit MapGraphicsObject(bool sizeIsZoomInvariant, QObject *parent = 0);

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
    double zValue;
    bool _selected;

    QString _toolTip;

    MapGraphicsObject::MapGraphicsObjectFlag _flags;

    bool _constructed;
};
Q_DECLARE_OPERATORS_FOR_FLAGS(MapGraphicsObject::MapGraphicsObjectFlags)

#endif // MAPGRAPHICSOBJECT_H
