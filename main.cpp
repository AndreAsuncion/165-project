#include <QApplication>
#include <QIcon>
#include "game.h"

Game * game;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QIcon icon(":/misc/icon.ico");
    app.setWindowIcon(icon);

    game = new Game();
    game->show();
    game->displayMainMenu();

    return app.exec();
}
