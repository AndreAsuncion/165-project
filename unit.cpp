#include "unit.h"

// constructor

// this first constructor is to set the player upon starting the game
Unit::Unit(QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent), maxHealthPoints(10), attackPower(2), level(1), type(1) {}

// enemy constructor
Unit::Unit(int hp, int ap, int lvl, QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent), maxHealthPoints(hp), attackPower(ap), level(lvl), type(1) {}

// variable getters
int Unit::getHP()
{
    return this->maxHealthPoints;
}

int Unit::getAP()
{
    return this->attackPower;
}

int Unit::getLVL()
{
    return this->level;
}

int Unit::getTYPE()
{
    return this->type;
}

QString Unit::getName()
{
    return this->name;
}

// variable setters
void Unit::setHP(int x)
{
    maxHealthPoints = x;
}

void Unit::setAP(int x)
{
    attackPower = x;
}

void Unit::setLVL(int x)
{
    level = x;
}

void Unit::setTYPE(int x)
{
    type = x;
}

void Unit::setName(QString string)
{
    name = string;
}

// variable modifyers
void Unit::changeHealth(int x)
{
    // int x will be negative for damage, positive for healing
    healthPoints += x;
}
