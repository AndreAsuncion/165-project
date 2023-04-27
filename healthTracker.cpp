#include "healthTracker.h"

healthTracker::healthTracker(Unit *unit, QGraphicsItem *parent) : QGraphicsRectItem(parent), unit(unit)
{
    // the box holding the numbers
    setRect(0,0,200,50);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::black);
    setBrush(brush);

    // the numbers
    text = new QGraphicsTextItem(QString("HP: %1/%2").arg(unit->getHP()).arg(unit->getMHP()), this);
    text->setDefaultTextColor(Qt::white);
    text->setFont(QFont("impact",25));
    int xPos = rect().width()/2 - text->boundingRect().width()/2;
    int yPos = rect().height()/2 - text->boundingRect().height()/2;
    text->setPos(xPos,yPos);
}

void healthTracker::updateText()
{
    text->setPlainText(QString("HP: %1/%2").arg(unit->getHP()).arg(unit->getMHP()));
}
