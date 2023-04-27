#include "gui.h"
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QBrush>

GUI::GUI(int x, QString string, QGraphicsItem *parent) :QGraphicsRectItem(parent), index(x)
{
    // draw rect
    setRect(0,500,800,100);
    QBrush panelBrush;
    panelBrush.setStyle(Qt::SolidPattern);
    panelBrush.setColor(QColorConstants::Svg::blue);
    setBrush(panelBrush);
    setOpacity(1);

    // draw the text
    text = new QGraphicsTextItem(string,this);
    text->setFont(QFont("impact", 40));
    int xPos = rect().width()/2 - text->boundingRect().width()/2;
    int yPos = 510;
    text->setPos(xPos,yPos);
}

GUI::GUI(QGraphicsItem *parent) :QGraphicsRectItem(parent)
{
    // draw rect
    setRect(0,500,800,100);
    QBrush panelBrush;
    panelBrush.setStyle(Qt::SolidPattern);
    panelBrush.setColor(QColorConstants::Svg::blue);
    setBrush(panelBrush);
    setOpacity(1);
}

void GUI::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit clicked(index);
}
