#include <iostream>
#include <Game.h>
#include <SDL2/SDL.h>

const int WIDTH = 800, HEIGHT = 600;

int main ( int argc, char* argv[] )
{
    Game game = Game();

    bool gameInitRst = game.Initialize();
    if ( gameInitRst == true ){
        game.RunLoop();
    }
    game.Shutdown();

    return EXIT_SUCCESS;
}