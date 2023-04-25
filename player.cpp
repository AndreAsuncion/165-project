#include "player.h"


Player::Player(QGraphicsItem *parent): Unit(parent), experiencePoints(0)
{

}

// variable getter
int Player::getXP()
{
    return this->experiencePoints;
}

// variable modifyer
void Player::changeXP(int x)
{
    experiencePoints += x;
}
