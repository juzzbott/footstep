#ifndef INTERNALGRAPHICSOBJECT_H
#define INTERNALGRAPHICSOBJECT_H

#include <QGraphicsObject>
#include <QPointer>
#include <QHash>

#include "controls/mapgraphics/mapgraphicsobject.h"

class InternalGraphicsObject : public QGraphicsObject
{
    Q_OBJECT



public:
    explicit InternalGraphicsObject(MapGraphicsObject *mgObj, QGraphicsItem *parent = 0);

    virtual ~InternalGraphicsObject();

    /**
     * @brief Virtual method from QGraphicsItem
     * @return
     */
    //virtual QRectF boundingRect() const;

    /**
     * @brief Virtual method from QGraphicsItem
     * @param point
     * @return
     */
    //bool contains (const QPointF &point) const;

    /**
     * @brief Virtual method from QGraphicsItem
     * @param painter
     * @param option
     * @param widget
     */
    //virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    /**
     * @brief Overrides setSelected from QGraphicsItem
     * @param selected
     */
    void setSelected(bool selected);

private:
    void setMapGraphicsObj(MapGraphicsObject *mapGraphicsObj);

    QPointer<MapGraphicsObject> _mapGraphicsObj;

};

#endif // INTERNALGRAPHICSOBJECT_H
