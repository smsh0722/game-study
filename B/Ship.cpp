#include "Ship.h"
#include "Game.h"

Ship::Ship( Game* game )
    :Actor(game)
{
    // TODO: Do other things
}

void Ship::UpdateActor( float deltaTime )
{
    Vector2 curPosition = this->GetPosition();
    curPosition.x += mRightSpeed * deltaTime;
    curPosition.y += mDownSpeed * deltaTime;
    
    if ( curPosition.x > 1000.0f ){
        curPosition.x = 1000.0f;
    }
    else if ( curPosition.x < 0.0f ){
        curPosition.x = 0.0f;
    }

    if ( curPosition.y > 700.0f ){
        curPosition.y = 700.0f;
    }
    else if ( curPosition.y < 0.0f ){
        curPosition.y = 0.0f;
    }
}

void Ship::ProcessKeyboard( const uint8_t* state )
{
    mDownSpeed = 0;
    mRightSpeed = 0;
    if ( state[SDL_SCANCODE_W] ){
        mDownSpeed -= 100.0f;
    }
    if ( state[SDL_SCANCODE_S] ){
        mDownSpeed += 100.0f;
    }
    if ( state[SDL_SCANCODE_A] ){
        mRightSpeed -= 100.0f;
    }
    if ( state[SDL_SCANCODE_D] ){
        mRightSpeed += 100.0f;
    }
}