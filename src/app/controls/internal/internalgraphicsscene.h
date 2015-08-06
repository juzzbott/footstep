#ifndef INTERNALGRAPHICSSCENE_H
#define INTERNALGRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QPointer>

#include "../app/controls/mapscene.h"

class InternalGraphicsScene : public QGraphicsScene
{

    Q_OBJECT

public:
    explicit InternalGraphicsScene(MapScene *mapScene, QObject *parent = 0);

signals:

private slots:
    void handleZoomLevelChanged();

private:
    void setMapScene(MapScene * mapScene);

    QPointer<MapScene> _mapScene;

};

#endif // INTERNALGRAPHICSSCENE_H
