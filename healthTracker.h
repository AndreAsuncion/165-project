#ifndef HEALTHTRACKER_H
#define HEALTHTRACKER_H

#include "unit.h"
#include <QGraphicsTextItem>
#include <QGraphicsRectItem>
#include <QBrush>

class healthTracker : public QObject, public QGraphicsRectItem
{
public:
    healthTracker(Unit *unit, QGraphicsItem *parent = NULL);
    void updateText();

private:
    Unit *unit;
    QGraphicsTextItem *text;
};

#endif // HEALTHTRACKER_H
