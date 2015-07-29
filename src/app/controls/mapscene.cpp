#include <QGraphicsScene>

#include "mapscene.h"

MapScene::MapScene(QObject *parent) : QGraphicsScene(parent)
{

}

MapScene::~MapScene() {

    //foreach(QObject *item, _items) {
    //    this->removeItem(item);
    //}

}

//void MapScene::addItem(QObject *item) {
//
//    // Validate the item
//    if (item == 0) {
//        return;
//    }
//
//    _items.insert(item);
//    this->itemAdded(item);
//
//}
//
//void MapScene::removeItem(QObject *item) {
//
//    // Validate the item
//    if (item == 0) {
//        return;
//    }
//
//    _items.remove(item);
//    this->itemRemoved(item);
//
//}
//
//QSet<QObject*> MapScene::items() const {
//    return _items;
//}
//
//void MapScene::handleNewItemAdded(QObject *item) {
//    this->addItem(item);
//}
//
//void MapScene::handleItemDestroyed(QObject *item) {
//    /*
//      We have to be careful with this casted pointer as technically at this point the MapGraphicsObject
//      portion of it has been destroyed. This signal comes from the QObject destructor.
//    */
//
//    QObject *mapObj = (QObject*)item;
//    this->removeItem((mapObj));
//
//}
