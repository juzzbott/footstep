#include "internalgraphicsview.h"

#include <QWheelEvent>

InternalGraphicsView::InternalGraphicsView(QWidget *parent) : QGraphicsView(parent)
{
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

InternalGraphicsView::InternalGraphicsView(QGraphicsScene *scene, QWidget *parent) : QGraphicsView(scene, parent)
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
    this->hadWheelEvent(event);
    if (!event->isAccepted()) {
        QGraphicsView::wheelEvent(event);
    }

}
