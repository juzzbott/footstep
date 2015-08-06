#include <QtDebug>

#include "internalgraphicsscene.h"
#include "../app/controls/mapscene.h"

InternalGraphicsScene::InternalGraphicsScene(MapScene *mapScene, QObject *parent) : QGraphicsScene(parent)
{

    // Set the map scene
    this->setMapScene(mapScene);

    // CONNECT

}

void InternalGraphicsScene::setMapScene(MapScene *mapScene) {

    // Set the map scene
    _mapScene = mapScene;

    // Ensure the mapScene is not null
    if (_mapScene.isNull()) {
        qWarning() << this << "mapScene is null.";
        return;
    }

    // CONNECT

}

void InternalGraphicsScene::handleZoomLevelChanged() {
    // Handle the zoom changed
}
