#ifndef TILE_H
#define TILE_H

#include <QGraphicsPolygonItem>

class Tile: public QGraphicsPolygonItem
{
public:
    // constructor
    Tile(QGraphicsItem * parent=NULL);

    // getters

private:
    // Unit* occupant; generic unit file
    int x, y;
};

#endif // TILE_H
