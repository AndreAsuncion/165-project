#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsRectItem>
#include <QtGlobal>
#include <QTime>
#include <QPixmap>
#include <QList>
#include <QIcon>
#include <QDebug>
#include "unit.h"
#include "button.h"
#include "gui.h"
#include "healthTracker.h"
#include "player.h"

class Game: public QGraphicsView
{
    Q_OBJECT
public:
    // constructor
    Game(QWidget * parent=NULL);

    // public methods
    void displayMainMenu();
    void startCombat();
    void textBox(int x, QString string); // makes a text box that contains the passed string
    void gameOver();
    void endCombat();
    int damageCalc(int x, Unit* defender);
    int getRandomInt(int min, int max); // randomizer

    //public attributes
    QGraphicsScene * scene;

    // does it what says
    Unit* createRandomEnemy(int minHP, int maxHP, int maxAP, int level);
public slots:
    void start();

    // these slots will deal with the GUI
    void playerMenu(); // Loads the buttons
    void enemyAttack();
    void abilityMenu();
    void playerAction(int x);
    void menuNav(int x);
    //void playerAction(); was for testing purposes
private:
    Button *fiteButton;
    Button *itemButton;
    Button *circleButton;
    Button *triangleButton;
    Button *squareButton;
    Button *backButton;
    Button *testButton;
    GUI *panel;
    healthTracker *enemyHealthText;
    healthTracker *playerHealthText;
};

#endif // GAME_H
