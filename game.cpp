#include "game.h"

Player * player;
Unit * enemy;
QList<QString> imagePaths = {":/enemies/ram.png",":/enemies/vicuna.png", ":/enemies/horse.png", ":/enemies/dog.png"};
QList<QString> enemyName = {"Ram","Vicuna","Horse", "Dog"};
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
    // clearing the scene
    scene->clear();

    // initializing player at the start, lvl 1, base stats
    player = new Player();
    playerHealthText = new healthTracker(player);
    playerHealthText->setPos(0,450);
    playerHealthText->setZValue(1000);
    scene->addItem(playerHealthText);

    // starts first instance of game/combat
    startCombat();
}

void Game::playerMenu()
{
    if(player->getHP() <= 0)
    {
        textBox(7, QString("You have been defeated..."));
        return;
    }

    panel = new GUI();
    scene->addItem(panel);

    // drawing the buttons, there's going to be two a fight and an item button
    fiteButton = new Button(1, QString("Basic Attack"));
    fiteButton->setPos(0, 525);
    connect(fiteButton, SIGNAL(clicked(int)), this, SLOT(playerAction(int)));
    scene->addItem(fiteButton);

    // it used to be items but I changed it to abilities
    itemButton = new Button(QString("Ability"));
    itemButton->setPos(200,525);
    connect(itemButton,SIGNAL(clicked()),this,SLOT(abilityMenu()));
    scene->addItem(itemButton);
}

void Game::abilityMenu()
{
    //remove unneeded buttons
    scene->removeItem(fiteButton);
    scene->removeItem(itemButton);

    // drawing the buttons
    circleButton = new Button(2, QString("Circle"));
    circleButton->setPos(0,525);
    connect(circleButton,SIGNAL(clicked(int)), this, SLOT(playerAction(int)));
    scene->addItem(circleButton);

    triangleButton = new Button(3, QString("Triangle"));
    triangleButton->setPos(200,525);
    connect(triangleButton,SIGNAL(clicked(int)), this, SLOT(playerAction(int)));
    scene->addItem(triangleButton);

    squareButton = new Button(4, QString("Square"));
    squareButton->setPos(400,525);
    connect(squareButton,SIGNAL(clicked(int)), this, SLOT(playerAction(int)));
    scene->addItem(squareButton);

    backButton = new Button(QString("Back"));
    backButton->setPos(600,525);
    connect(backButton,SIGNAL(clicked()),this,SLOT(playerMenu()));
    scene->addItem(backButton);
}

int Game::damageCalc(int x, Unit* defender)
{
    // rock paper scissors
    // circle == 2, powerful to square, weak to triangle
    // triangle == 3, powerful to circle, weak to square
    // square == 4, powerful to triangle, weak to circle

    //qDebug() << x << " type attack was used";

    int type = defender->getTYPE();

    //qDebug() << type;
    //int damage = player->getAP();
    if(x == type)
    {
        return player->getAP();
    }
    else if((x == 2 && type == 4) || (x == 3 && type == 2) || (x == 4 && type == 3))
    {
        //qDebug() << x << " attack was very effective!";
        return (player->getAP() * 2);
    }
    else if((x == 2 && type == 3) || (x == 3 && type == 4) || (x == 4 && type == 2))
    {
        //qDebug() << x << " attack wasn't very effective!";
        return (player->getAP() / 2);
    }

    return player->getAP();
}

void Game::playerAction(int x)
{
    if(x == 1)
    {
        scene->removeItem(fiteButton);
        scene->removeItem(itemButton);
    }
    else
    {
        scene->removeItem(circleButton);
        scene->removeItem(triangleButton);
        scene->removeItem(squareButton);
        scene->removeItem(backButton);
    }

    int damage = damageCalc(x,enemy);

    // qDebug() << "dealt " << damage;

    QString message = QString("You dealt %1 damage to %2").arg(damage).arg(enemy->getName());
    enemy->changeHealth(-damage);

    if(damage > player->getAP())
    {
        textBox(4, message);
        return;
    }
    else if(damage < player->getAP())
    {
        textBox(5, message);
        return;
    }
    else
    {
        textBox(3, message);
        return;
    }


    if (enemy->getHP() <= 1) {

        if(enemy->getLVL() > player->getLVL()){
            int expGained = ( (enemy->getLVL() + 2 ) );
            player->setLVL((player->getLVL()+expGained));


            textBox(2, QString("XP Gained: %1").arg(expGained));
        }
        else {
            int expGained = (enemy->getLVL() );
            player->setLVL( (player->getLVL()+expGained) );
            textBox(2, QString("XP Gained: %1").arg(expGained));
        }

    }
}


void Game::enemyAttack()
{
    if(enemy->getHP() <= 0)
    {
        qDebug() << "animal dead";
        textBox(6, QString("%1 was defeated").arg(enemy->getName()));
        return;
    }

    player->changeHealth(-enemy->getAP());

    textBox(1, QString("%1 attacked dealing %2 damage!").arg(enemy->getName()).arg(enemy->getAP()));
}

void Game::endCombat()
{
    startCombat();
}

void Game::gameOver(){
    scene->clear();

    QGraphicsTextItem * titleText = new QGraphicsTextItem(QString("Game Over"));
    QFont titleFont("impact", 50);
    titleText->setFont(titleFont);
    int ttxPos = this->width()/2 - titleText->boundingRect().width()/2;
    int ttyPos = 150;
    titleText->setPos(ttxPos,ttyPos);
    scene->addItem(titleText);

    Button * playButton = new Button(QString("Restart"));
    int bxPos = this->width()/2 - playButton->boundingRect().width()/2;
    int byPos = 275;
    playButton->setPos(bxPos,byPos);
    connect(playButton,SIGNAL(clicked()),this,SLOT(start()));
    scene->addItem(playButton);

    Button * quitButton = new Button(QString("Quit"));
    int qxPos = this->width()/2 - quitButton->boundingRect().width()/2;
    int qyPos = 350;
    quitButton->setPos(qxPos,qyPos);
    connect(quitButton,SIGNAL(clicked()),this,SLOT(close()));
    scene->addItem(quitButton);
}

// Call this function to make the blue GUI rectangle thing have text in it
void Game::textBox(int x, QString string)
{
    // draws the blue rectangle for the battle GUI
    panel = new GUI(x, string);
    connect(panel,SIGNAL(clicked(int)),this,SLOT(menuNav(int)));
    scene->addItem(panel);
}

void Game::menuNav(int x)
{
    // hides the textbox
    scene->removeItem(panel);

    switch(x)
    {
    case(1):
        playerMenu();
        break;
    case(2):
        startCombat();
        break;
    case(3):
        enemyAttack();
        break;
    case(4):
        textBox(3, QString("It was super effective!"));
        break;
    case(5):
        textBox(3, QString("It was not very effective..."));
        break;
    case(6):
        endCombat();
        break;
    case(7):
        gameOver();
    }
}

void Game::displayMainMenu()
{
    // print title
    QGraphicsTextItem * titleText = new QGraphicsTextItem(QString("Animal Fight Club"));
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
    enemy = createRandomEnemy(player->getMHP() - 3, player->getMHP(), player->getAP() - 3, player->getLVL());
    textBox(1, QString("A wild %1 is approaching!").arg(enemy->getName()));
}

Unit *Game::createRandomEnemy(int minHP, int maxHP, int maxAP, int level)
{
    int randomIndex = getRandomInt(0,(imagePaths.size() - 1));
    //int imageIndex = (player->getLVL() > 25) ? 5 : ((player->getLVL()-1) / 5);

    // draws the background before drawing the enemy sprite
    QGraphicsPixmapItem * enemyBG = new QGraphicsPixmapItem();
    enemyBG->setPixmap(imageBG[0]);
    scene->addItem(enemyBG);

    // creates new enemy
    enemy = new Unit();

    // draws the enemy sprite
    QGraphicsPixmapItem * enemySprite = new QGraphicsPixmapItem();
    enemySprite->setPixmap(imagePaths[randomIndex]);
    enemySprite->setPos(100,100);
    scene->addItem(enemySprite);

    // setting the members of enemy
    enemy->setLVL(level);
    enemy->setMHP(getRandomInt(minHP+1,maxHP));
    enemy->setAP(getRandomInt(1,maxAP));
    enemy->setTYPE(getRandomInt(2,4));
    enemy->setName(enemyName[randomIndex]);

    // health tracker
    enemyHealthText = new healthTracker(enemy);
    enemyHealthText->setPos(650,0);
    scene->addItem(enemyHealthText);

    return enemy;
}
