#include "internalgraphicsview.h"

#include <QWheelEvent>

InternalGraphicsView::InternalGraphicsView(QWidget *parent) : QGraphicsView(paremt)
{
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

InternalGraphicsView::InternalGraphicsView(QGraphicsScene *scene, QWidget *parent) : QGraphicsView(scene, paremt)
{
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

InternalGraphicsView::~InternalGraphicsView()
{
}

// Wheel event
void InternalGraphicsView::wheelEvent(QWheelEvent *event) {

    event->setAccepted(false);
    this->handleWheelEvent(event);
    if (!event->isAccepted()) {
        QGraphicsView.wheelEvent(event);
    }

}
