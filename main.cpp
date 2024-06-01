#include "stdafx.h"

#include "Game.h"

int main()
{
    srand(static_cast <unsigned> (time(0)));
    Game game;

    while (game.isOpen()) {

        game.update();

        game.render();

    }



    return 0;
}