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
Unit * enemy;
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

//void Game::playerMenu()
//{
//    // clearing the GUI of the text
//    GUI * panel = new GUI();
//    scene->addItem(panel);

//    // drawing the buttons, there's going to be two a fight and an item button
//    fiteButton = new Button(QString("Basic Attack"));
//    int fbxPos = 0;
//    int fbyPos = 525;
//    fiteButton->setPos(fbxPos,fbyPos);

//    scene->addItem(fiteButton);

//    // it used to be items but I changed it to abilities
//    itemButton = new Button(QString("Ability"));
//    int ibxPos = 200;
//    int ibyPos = 525;
//    itemButton->setPos(ibxPos,ibyPos);
//    connect(itemButton,SIGNAL(clicked()),this,SLOT(abilityMenu()));
//    connect(fiteButton, SIGNAL(clicked()), this, SLOT(basicAttack()));
//    connect(fiteButton, SIGNAL(clicked()), this, SLOT(disableFightButton()));

//    scene->addItem(itemButton);

//}


void Game::playerMenu()
{
    // clearing the GUI of the text
    GUI * panel = new GUI();
    scene->addItem(panel);

    // drawing the buttons, there's going to be two a fight and an item button
    fiteButton = new Button(QString("Basic Attack"));
    int fbxPos = 0;
    int fbyPos = 525;
    fiteButton->setPos(fbxPos,fbyPos);

    scene->addItem(fiteButton);

    // it used to be items but I changed it to abilities
    itemButton = new Button(QString("Ability"));
    int ibxPos = 200;
    int ibyPos = 525;
    itemButton->setPos(ibxPos,ibyPos);
    connect(itemButton,SIGNAL(clicked()),this,SLOT(abilityMenu()));
    connect(fiteButton, SIGNAL(clicked()), this, SLOT(basicAttack()));
    connect(fiteButton, SIGNAL(clicked()), this, SLOT(disableFightButton()));
    connect(this, SIGNAL(enemyDefeated()), this, SLOT(showFightButton())); // new connection

    scene->addItem(itemButton);
}


void Game::abilityMenu()
{
    //remove unneeded buttons
    scene->removeItem(fiteButton);
    scene->removeItem(itemButton);

    // drawing the buttons
    circleButton = new Button(QString("Circle"));
    int cbxPos = 0;
    int cbyPos = 525;
    circleButton->setPos(cbxPos,cbyPos);
    connect(circleButton,SIGNAL(clicked()),this,SLOT(moveCircle()));
    scene->addItem(circleButton);

    // it used to be items but I changed it to abilities
    triangleButton = new Button(QString("Triangle"));
    int tbxPos = 200;
    int tbyPos = 525;
    triangleButton->setPos(tbxPos,tbyPos);
    connect(triangleButton,SIGNAL(clicked()),this,SLOT(moveTriangle()));
    scene->addItem(triangleButton);

    squareButton = new Button(QString("Square"));
    int sbxPos = 400;
    int sbyPos = 525;
    squareButton->setPos(sbxPos,sbyPos);
    connect(squareButton,SIGNAL(clicked()),this,SLOT(moveSquare()));
    scene->addItem(squareButton);

    backButton = new Button(QString("Back"));
    int bbxPos = 600;
    int bbyPos = 525;
    backButton->setPos(bbxPos,bbyPos);
    connect(backButton,SIGNAL(clicked()),this,SLOT(playerMenu()));
    scene->addItem(backButton);
}

void Game::basicAttack()
{
    //remove unneeded buttons
    scene->removeItem(fiteButton);
    scene->removeItem(itemButton);

    int attackPower = player->getAP();
    int enemyAttack = enemy->getAP();

    int enemyHealth = enemy->getHP();

    enemyHealth -= attackPower;

    enemy->setHP(enemyHealth);

    int playerHealth = player->getHP();

    playerHealth -= enemyAttack;

    player->setHP(playerHealth);


    QGraphicsTextItem *enemyHealthText = new QGraphicsTextItem();
    enemyHealthText->setPlainText(QString("Enemy HP: ") + QString::number(enemy->getHP()));
    enemyHealthText->setDefaultTextColor(Qt::white);
    enemyHealthText->setFont(QFont("times",16));
    enemyHealthText->setPos(400, 525);
    scene->addItem(enemyHealthText);

    backButton = new Button(QString("Back"));
    int bbxPos = 600;
    int bbyPos = 525;
    backButton->setPos(bbxPos,bbyPos);
    connect(backButton,SIGNAL(clicked()),this,SLOT(playerMenu()));
    scene->addItem(backButton);

//    if(enemy->getHP() <= 0){
//        emit enemyDefeated(); // new signal
//    }
}

//void Game::basicAttack(Unit& enemy)
//{
//    //remove unneeded buttons
//    scene->removeItem(fiteButton);
//    scene->removeItem(itemButton);

//    int attackPower = player->getAP();
//    int enemyAttack = enemy.getAP();

//    int enemyHealth = enemy.getHP();

//    enemyHealth -= attackPower;

//    enemy.setHP(enemyHealth);

//    int playerHealth = player->getHP();

//    playerHealth -= enemyAttack;

//    player->setHP(playerHealth);


//    QGraphicsTextItem *enemyHealthText = new QGraphicsTextItem();
//    enemyHealthText->setPlainText(QString("Enemy HP: ") + QString::number(enemy.getHP()));
//    enemyHealthText->setDefaultTextColor(Qt::white);
//    enemyHealthText->setFont(QFont("times",16));
//    enemyHealthText->setPos(400, 525);
//    scene->addItem(enemyHealthText);
//}


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
    enemy = createRandomEnemy(player->getHP() - (player->getLVL() * 3), player->getHP(), player->getAP() - (player->getLVL() * 5), player->getAP() - (player->getLVL() * 3), player->getLVL());
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
    enemy = new Unit();
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
