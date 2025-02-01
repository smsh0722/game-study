#include "Game.h"
#include "SDL2/SDL_image.h"
#include "Actor.h"
#include "Ship.h"
#include <algorithm>

Game::Game()
:mWindow(nullptr),
mRenderer(nullptr),
mIsRunning(true),
mUpdatingActors(false)
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

    if( IMG_Init( IMG_INIT_PNG) == 0 ){
        SDL_Log( "Unable to init sdl_image: %s", SDL_GetError() );
        return false;
    }
    
    // TODO: LoadData();

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
    // TODL: unload Data
    IMG_Quit();
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

void Game::ProcessInput()
{
    SDL_Event event;
    while ( SDL_PollEvent(&event) ){
        switch (event.type)
        {
        case SDL_QUIT:
            mIsRunning = false;
            break;
        
        default:
            break;
        }
    }

    const Uint8* state = SDL_GetKeyboardState(NULL);
    if ( state[SDL_SCANCODE_ESCAPE] ){
        mIsRunning = false;
    }

    ship->ProcessKeyboard(state);
}

void Game::UpdateGame()
{
    while ( SDL_TICKS_PASSED( SDL_GetTicks(), mTickCount+16 ) == false ){
        ;
    }

    // Get deltaTime
    float deltaTime = (SDL_GetTicks() - mTickCount) / 1000.0f;
    if ( deltaTime > 0.05f ){ // min 20frame delta time
        deltaTime = 0.05f;
    }
    mTickCount = SDL_GetTicks();

    // Update all Actors
    mUpdatingActors = true;
    for ( int i = 0; i < mActors.size(); i++ ){
        Actor* actor = mActors[i];

        actor->Update( deltaTime );
    }
    mUpdatingActors = false;

    // Add pending actors
    for ( int i = 0; i < mPendingActors.size(); i++ ){
        Actor* actor = mPendingActors[i];

        mActors.push_back(actor);
    }
    mPendingActors.clear();

    // Add Dead Actors
    std::vector<Actor*> deadActors;
    for ( int i = 0; i < mActors.size(); i++ ){
        Actor* actor = mActors[i];

        // TIP : 중간에서 지우면 문제 생길 수 있음
        Actor::State state = actor->GetState();
        if ( state == Actor::EDead ){
            deadActors.push_back(actor);
        }
    }

    // Remove dead actors
    for ( int i = 0; i < deadActors.size(); i++ ){
        delete deadActors[i];
        // TIP : destructor에서 mActor 스스로 관리.
    }
}

void Game::AddActor( class Actor* actor )
{
    if ( mUpdatingActors == true ){
        mPendingActors.push_back(actor);
    }
    else {
        mActors.push_back(actor);
    }
}

void Game::RemoveActor( class Actor* actor )
{
    std::vector<class Actor*>::iterator it = std::find(
        mPendingActors.begin(), mPendingActors.end(), actor
    );

    if ( it != mActors.end() ){
        // TIP : .erase()는 copying, moving 가능
        std::iter_swap(it, mPendingActors.end() - 1 );
        mPendingActors.pop_back();
    }
    else {
        it = std::find( mActors.begin(), mActors.end(), actor );

        if ( it != mActors.end() ){
            std::iter_swap(it, mActors.end() -1 );
            mActors.pop_back();
        }
    }
}