#ifndef INTERNALGRAPHICSVIEW_H
#define INTERNALGRAPHICSVIEW_H

#include <QGraphicsView>

class InternalGraphicsView : public QGraphicsView
{

    Q_OBJECT

public:
    explicit InternalGraphicsView(QWidget *parent = 0);
    InternalGraphicsView(QGraphicsScene *scene, QWidget *parent = 0);
    virtual ~InternalGraphicsView();

protected:
    virtual void wheelEvent(QWheelEvent *event);

signals:
    void hadWheelEvent(QWheelEvent *);

};

#endif // INTERNALGRAPHICSVIEW_H
