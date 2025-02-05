#include "Game.h"
#include "SDL2/SDL_image.h"
#include "Actor.h"
#include "Ship.h"
#include "SpriteComponent.h"
#include <algorithm>
#include "BGSpriteComponent.h"

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
    
    LoadData();

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
    UnloadData();
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

    mShip->ProcessKeyboard(state);
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
    for ( size_t i = 0; i < mActors.size(); i++ ){
        Actor* actor = mActors[i];

        actor->Update( deltaTime );
    }
    mUpdatingActors = false;

    // Add pending actors
    for ( size_t i = 0; i < mPendingActors.size(); i++ ){
        Actor* actor = mPendingActors[i];

        mActors.push_back(actor);
    }
    mPendingActors.clear();

    // Add Dead Actors
    std::vector<Actor*> deadActors;
    for ( size_t i = 0; i < mActors.size(); i++ ){
        Actor* actor = mActors[i];

        // TIP : 중간에서 지우면 문제 생길 수 있음
        Actor::State state = actor->GetState();
        if ( state == Actor::EDead ){
            deadActors.push_back(actor);
        }
    }

    // Remove dead actors
    for (auto it = deadActors.begin(); it != deadActors.end(); ) {
        delete *it;           // Delete the actor
        it = deadActors.erase(it); // Remove from the vector and move to the next element
    }
}

void Game::GenerateOutput()
{
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
	SDL_RenderClear(mRenderer);
	
	// Draw all sprite components
	for (auto sprite : mSprites)
	{
		sprite->Draw(mRenderer);
	}

	SDL_RenderPresent(mRenderer);
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

void Game::AddSprite( SpriteComponent* spriteComponent )
{
    int drawOrder = spriteComponent->GetDrawOrder();
    std::vector<class SpriteComponent*>::iterator it = mSprites.begin();
    for  (; it != mSprites.end(); it++ ){
        if ( (*it)->GetDrawOrder() > drawOrder ){
            break;
        }
    }

    mSprites.insert( it, spriteComponent );
}

void Game::RemoveSprite( SpriteComponent* spriteComponent )
{
    std::vector<class SpriteComponent*>::iterator it = 
        std::find( mSprites.begin(), mSprites.end(), spriteComponent );

    if ( it != mSprites.end() ){
        std::iter_swap( it, mSprites.end() - 1 );
        mSprites.pop_back();
    }
}

SDL_Texture* Game::GetTexture( const std::string& fileName )
{
    SDL_Texture* tex = nullptr;

    std::unordered_map<std::string, SDL_Texture*>::iterator it;
    it = mTextures.find(fileName);
    if ( it != mTextures.end() ){
        return it->second;
    }
    else {
        SDL_Surface* surf = IMG_Load(fileName.c_str());
		if (!surf)
		{
			SDL_Log("Failed to load texture file %s", fileName.c_str());
			return nullptr;
		}

		// Create texture from surface
		tex = SDL_CreateTextureFromSurface(mRenderer, surf);
		SDL_FreeSurface(surf);
		if (!tex)
		{
			SDL_Log("Failed to convert surface to texture for %s", fileName.c_str());
			return nullptr;
		}

		mTextures.emplace(fileName.c_str(), tex);
    }
    return tex;
}

void Game::LoadData()
{
	// Create player's ship
	mShip = new Ship(this);
	mShip->SetPosition(Vector2(100.0f, 384.0f));
	mShip->SetScale(1.5f);

	// Create actor for the background (this doesn't need a subclass)
	Actor* temp = new Actor(this);
	temp->SetPosition(Vector2(512.0f, 384.0f));
	// Create the "far back" background
	BGSpriteComponent* bg = new BGSpriteComponent(temp);
	bg->SetScreenSize(Vector2(1024.0f, 768.0f));
	std::vector<SDL_Texture*> bgtexs = {
		GetTexture("Assets/Farback01.png"),
		GetTexture("Assets/Farback02.png")
	};
	bg->SetBGTextures(bgtexs);
	bg->SetScrollSpeed(-100.0f);
	// Create the closer background
	bg = new BGSpriteComponent(temp, 50);
	bg->SetScreenSize(Vector2(1024.0f, 768.0f));
	bgtexs = {
		GetTexture("Assets/Stars.png"),
		GetTexture("Assets/Stars.png")
	};
	bg->SetBGTextures(bgtexs);
	bg->SetScrollSpeed(-200.0f);
}

void Game::UnloadData()
{
	// Delete actors
	// Because ~Actor calls RemoveActor, have to use a different style loop
	while (!mActors.empty())
	{
		delete mActors.back();
	}

	// Destroy textures
	for (auto i : mTextures)
	{
		SDL_DestroyTexture(i.second);
	}
	mTextures.clear();
}