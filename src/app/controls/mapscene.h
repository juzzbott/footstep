#ifndef MAPSCENE_H
#define MAPSCENE_H

#include <QObject>
#include <QWidget>
#include <QGraphicsScene>
#include <QSet>

#include "../core/geopoint.h"

class MapScene : public QGraphicsScene
{
    Q_OBJECT

public:
    MapScene(QObject *parent = 0);
    virtual ~MapScene();

    /**
     * @brief Adds a new item to the map scene.
     * @param item The item to add to the scene.
     */
    //void addItem(QObject *item);

    /**
     * @brief Removes the specified item from the scene.
     * @param item The item to remove from the scene.
     */
    //void removeItem(QObject *item);

    /**
     * @brief Returns the list of items in the map scene.
     * @return QList<QObject*>
     */
    //QSet<QObject*> items() const;

private:

    // Fields
    //QSet<QObject*> _items;

signals:

    /**
     * @brief Fired when an item is added to the scene.
     * @param item The item that was added.
     */
    //void itemAdded(QObject *item);
    //
    ///**
    // * @brief Fired when an item is removed from the scene.
    // * @param item The item that is removed.
    // */
    //void itemRemoved(QObject *item);

private slots:
    //void handleNewItemAdded(QObject *newItem);
    //void handleItemDestroyed(QObject *item);


};

#endif // MAPSCENE_H
