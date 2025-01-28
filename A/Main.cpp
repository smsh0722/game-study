#include <iostream>
#include "Game.h"

int main( int argc, char* argv[] )
{
    Game game = Game();

    bool gameInitRst = game.Initialize();
    if ( gameInitRst == true ){
        game.RunLoop();
    }
    game.Shutdown();

    return EXIT_SUCCESS;
}