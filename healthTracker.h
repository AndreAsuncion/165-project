#ifndef HEALTHTRACKER_H
#define HEALTHTRACKER_H

#include "unit.h"

class healthTracker : public QObject, public QGraphicsRectItem
{
public:
    healthTracker(Unit *unit, QGraphicsItem *parent = NULL);
public slots:
    void updateText();
private:
    Unit *unit;
    QGraphicsTextItem *text;
};

#endif // HEALTHTRACKER_H
