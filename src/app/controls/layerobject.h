#ifndef LAYEROBJECT_H
#define LAYEROBJECT_H

#include <QObject>

class LayerObject : public QObject
{

    Q_OBJECT

public:
    enum LayerObjectType {
        ObjectIsMovable = 0x01,
        ObjectIsSelectable = 0x02,
        ObjectIsFocusable = 0x04
    };
    Q_DECLARE_FLAGS(LayerObjectTypes, LayerObjectType)

public:
    explicit LayerObject();
};

#endif // LAYEROBJECT_H
