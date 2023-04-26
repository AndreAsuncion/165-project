#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include "unit.h"
#include "button.h"
#include "gui.h"

class Game: public QGraphicsView
{
    Q_OBJECT
public:
    // constructor
    Game(QWidget * parent=NULL);

    // public methods
    void displayMainMenu();
    void startCombat();
    int getRandomInt(int min, int max); // randomizer

    //public attributes
    QGraphicsScene * scene;

    // something
    Unit* createRandomEnemy(int minHP, int maxHP, int minAP, int maxAP, int level);
public slots:
    void start();

    // these slots will deal with the GUI
    void playerMenu(); // Loads the buttons
    void basicAttack();
    void enemyAttack();
    void abilityMenu();
    void textBox(QString string); // makes a text box
private:
    Button *fiteButton;
    Button *itemButton;
    Button *circleButton;
    Button *triangleButton;
    Button *squareButton;
    Button *backButton;
    GUI *panel;
    // void drawGUI();
};

#endif // GAME_H
