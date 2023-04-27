#ifndef PLAYER_H
#define PLAYER_H

#include "unit.h"

class Player: public Unit
{
    Q_OBJECT
public:
    Player(QGraphicsItem * parent=NULL);

    // variable getter
    int getXP();

    // variable setter
    void setXP(int x);

    // variable modifyer
    void changeXP(int x);
private:
    int experiencePoints;
    int score;
};

#endif // PLAYER_H
