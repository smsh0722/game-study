#include "Game.h"

Game::Game()
:mWindow(nullptr),
mRenderer(nullptr),
mIsRunning(true)
{

}

bool Game::Initialize()
{
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0){
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

    mWindow = SDL_CreateWindow("Chapter2", 100, 100, 1024, 768, 0 );
    if ( mWindow == NULL ){
        SDL_Log("Unable to create sdl window: %s", SDL_GetError() );
        return false;
    }

    mRenderer = SDL_CreateRenderer( mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    if ( mRenderer == NULL ){
        SDL_Log("Unbale to cretae Renderer SDL: %s", SDL_GetError() );
        return false;
    }

    mTickCount = SDL_GetTicks();
    return true;
}

void Game::RunLoop()
{
    while (mIsRunning){
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

void Game::Shutdown()
{
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}