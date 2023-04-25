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
    GUI(QString string, QGraphicsItem * parent=NULL);
    GUI(QGraphicsItem * parent=NULL);

    // detect click
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
signals:
    void clicked();
private:
    QGraphicsTextItem * text;
};

#endif // GUI_H
