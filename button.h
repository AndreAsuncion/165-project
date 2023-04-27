#ifndef BUTTON_H
#define BUTTON_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsTextItem>
#include <QBrush>

class Button: public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    // constructor
    Button(QString string, QGraphicsItem* parent=NULL);
    Button(int x, QString string, QGraphicsItem* parent=NULL);

    //public methods
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
signals:
    void clicked();
    void clicked(int buttonType);
private:
    QGraphicsTextItem * text;
    int type;
};

#endif // BUTTON_H
