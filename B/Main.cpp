#pragma once
#include <iostream>
#include "Game.h"

int main ( int argc, char* argv[] )
{
    Game game = Game();
    bool initRst = game.Initialize();
    if( initRst == true ){
        game.RunLoop();
    }
    game.Shutdown();

    return 0;
}