#ifndef MAPGRAPHICSOBJECT_H
#define MAPGRAPHICSOBJECT_H

#include <QObject>

class MapGraphicsObject : public QObject
{
    Q_OBJECT
public:
    explicit MapGraphicsObject(QObject *parent = 0);

signals:

public slots:
};

#endif // MAPGRAPHICSOBJECT_H
