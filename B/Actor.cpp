#include "Actor.h"
#include "Game.h"
#include "Component.h"

Actor::Actor( Game* game )
    : mState(EAlive),
    mPosition(Vector2::Zero),
    mScale(1.0f),
    mRotation(0.0f),
    mGame(game)
{
    mGame->AddActor(this);
}

Actor::~Actor()
{
	mGame->RemoveActor(this);
	while (!mComponents.empty())
	{
		delete mComponents.back();
	}
}

void Actor::Update(float deltaTime )
{
    if ( mState == EAlive ){
        UpdateComponents( deltaTime );
        UpdateActor( deltaTime );
    }
}

void Actor::UpdateComponents( float deltaTime )
{
    for ( int i = 0; i < mComponents.size(); i++ ){
        Component* Component = mComponents[i];

        // TODO: Component->Update();
    }
}

void Actor::UpdateActor( float deltaTime )
{

}
