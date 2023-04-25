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

    // variable modifyer
    void changeXP(int x);
private:
    int experiencePoints;
};

#endif // PLAYER_H
