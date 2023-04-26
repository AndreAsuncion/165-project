#include "game.h"
#include "button.h"
#include "gui.h"
#include "player.h"
#include <QGraphicsTextItem>
#include <QGraphicsRectItem>
#include <QtGlobal>
#include <QTime>
#include <QPixmap>
#include <QList>
#include <QIcon>

Player * player;
QList<QString> imagePaths = {":/enemies/ram.png",":/enemies/vicuna.png", ":/enemies/horse.png", ":/enemies/dog.png"};
QList<QString> enemyName = {"ram","vicuna","horse", "dog"};
QList<QString> imageBG = {":/backgrounds/BG1.jpg"};

Game::Game(QWidget *parent)
{
    Q_UNUSED(parent); // it seems like everytime I fix an error 3 more pop up

    // set up the window
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(800,600);

    // set up the scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,800,600);
    setScene(scene);

}

int Game::getRandomInt(int min, int max)
{
    srand(QTime::currentTime().msec());
    return rand() % (max - min + 1) + min;
}

void Game::start()
{
    // initializing player at the start, lvl 1, base stats
    player = new Player();

    // clearing the scene
    scene->clear();

    // starts first instance of game/combat
    startCombat();
}

void Game::playerMenu()
{
    // clearing the GUI of the text
    GUI * panel = new GUI();
    scene->addItem(panel);

    // drawing the buttons, there's going to be two a fight and an item button
    Button * fiteButton = new Button(QString("Fight"));
    int fbxPos = 0;
    int fbyPos = 525;
    fiteButton->setPos(fbxPos,fbyPos);
    connect(fiteButton,SIGNAL(clicked()),this,SLOT(playerAction()));
    scene->addItem(fiteButton);

    // it used to be items but I changed it to abilities
    Button * itemButton = new Button(QString("Ability"));
    int ibxPos = 200;
    int ibyPos = 525;
    itemButton->setPos(ibxPos,ibyPos);
    connect(itemButton,SIGNAL(clicked()),this,SLOT(abilityMenu()));
    scene->addItem(itemButton);

    // player health
    // QGraphicsTextItem * playerHealth = new QGraphicsTextItem(QString("Work in Progress"));
}

void Game::textBox(QString string)
{
    // draws the blue rectangle for the battle GUI
    GUI * panel = new GUI(string);
    connect(panel,SIGNAL(clicked()),this,SLOT(playerMenu()));
    scene->addItem(panel);
}

void Game::displayMainMenu()
{
    // print title
    QGraphicsTextItem * titleText = new QGraphicsTextItem(QString("Animal Abuse"));
    QFont titleFont("impact", 50);
    titleText->setFont(titleFont);
    int ttxPos = this->width()/2 - titleText->boundingRect().width()/2;
    int ttyPos = 150;
    titleText->setPos(ttxPos,ttyPos);
    scene->addItem(titleText);

    // play button
    Button * playButton = new Button(QString("Play"));
    int bxPos = this->width()/2 - playButton->boundingRect().width()/2;
    int byPos = 275;
    playButton->setPos(bxPos,byPos);
    connect(playButton,SIGNAL(clicked()),this,SLOT(start()));
    scene->addItem(playButton);

    // quit button
    Button * quitButton = new Button(QString("Quit"));
    int qxPos = this->width()/2 - quitButton->boundingRect().width()/2;
    int qyPos = 350;
    quitButton->setPos(qxPos,qyPos);
    connect(quitButton,SIGNAL(clicked()),this,SLOT(close()));
    scene->addItem(quitButton);
}

void Game::startCombat()
{
    // function creates an enemy based on player's stats
    Unit * enemy = createRandomEnemy(player->getHP() - (player->getLVL() * 3), player->getHP(), player->getAP() - (player->getLVL() * 5), player->getAP() - (player->getLVL() * 3), player->getLVL());
    textBox(QString("A wild %1 is approaching!").arg(enemy->getName()));
}

Unit *Game::createRandomEnemy(int minHP, int maxHP, int minAP, int maxAP, int level)
{
    int randomIndex = getRandomInt(0,(imagePaths.size() - 1));

    // draws the background before drawing the enemy sprite
    QGraphicsPixmapItem * enemyBG = new QGraphicsPixmapItem();
    enemyBG->setPixmap(imageBG[level-1]);
    scene->addItem(enemyBG);



    // creates new enemy
    Unit * enemy = new Unit();
    QGraphicsPixmapItem * enemySprite = new QGraphicsPixmapItem();
    enemySprite->setPixmap(imagePaths[randomIndex]);
    enemySprite->setPos(100,100);
    scene->addItem(enemySprite);



    enemy->setLVL(level);
    enemy->setHP(getRandomInt(minHP,maxHP));
    enemy->setAP(getRandomInt(minAP,maxAP));
    enemy->setTYPE(getRandomInt(1,3));
    enemy->setName(enemyName[randomIndex]);

    return enemy;
}
