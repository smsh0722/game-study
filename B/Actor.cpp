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
        Component* component = mComponents[i];

        // TODO: Component->Update();
    }
}

void Actor::UpdateActor( float deltaTime )
{

}

void Actor::AddComponent(  Component* component )
{
    int order = component->GetUpdateOrder();
    std::vector<class Component*>::iterator it = mComponents.begin();
    for ( it; it != mComponents.end(); it++ ){
        if ( (*it)->GetUpdateOrder() > order ){
            mComponents.insert( it, component );
            break;
        }
    }
}

void Actor::RemoveComponent(  Component* component )
{
    int trg = -1;
    for ( int i = 0; i < mComponents.size(); i++ ){
        if ( mComponents[i] == component ){
            trg = i;
            break;
        }
    }

    if ( trg >= 0 ){
        mComponents.erase( mComponents.begin() + trg );
    }
}