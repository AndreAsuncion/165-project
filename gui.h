#ifndef GUI_H
#define GUI_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QFont>

class GUI: public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    // constructor
    GUI(int x, QString string, QGraphicsItem * parent=NULL);
    GUI(QGraphicsItem * parent=NULL);

    // detect click
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
signals:
    void clicked(int x);
private:
    QGraphicsTextItem * text;
    int index;
};

#endif // GUI_H
