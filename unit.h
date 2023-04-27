#ifndef UNIT_H
#define UNIT_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QFont>
#include <QDebug>
#include <QGraphicsTextItem>
#include <QGraphicsRectItem>
#include <QBrush>

class Unit: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    // constructor
    Unit(QGraphicsItem * parent=NULL);
    Unit(int hp, int ap, int lvl, QGraphicsItem * parent=NULL);

    // variable getters
    int getHP();
    int getAP();
    int getMHP();
    int getLVL();
    int getTYPE();
    QString getName();

    // variable setters
    void setHP(int x);
    void setMHP(int x);
    void setAP(int x);
    void setLVL(int x);
    void setTYPE(int x);
    void setName(QString string);

    // variable modifyers
    void changeHealth(int x);
signals:
    void healthChanged();
private:
    int maxHealthPoints, healthPoints, attackPower, level, type;
    QString name;
};

#endif // UNIT_H
