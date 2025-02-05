#include "Actor.h"
#include "Game.h"
#include "Component.h"
#include <algorithm>

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
    for ( size_t i = 0; i < mComponents.size(); i++ ){
        Component* component = mComponents[i];
        component->Update( deltaTime );
    }
}

void Actor::UpdateActor( float deltaTime )
{
}

void Actor::AddComponent(  Component* component )
{
    int order = component->GetUpdateOrder();
    std::vector<class Component*>::iterator it = mComponents.begin();
    for ( ; it != mComponents.end(); it++ ){
        if ( (*it)->GetUpdateOrder() > order ){
            break;
        }
    }

    mComponents.insert( it, component );
}

void Actor::RemoveComponent(  Component* component )
{
    std::vector<class Component*>::iterator it = std::find(
        mComponents.begin(), mComponents.end(), component
    );
    if ( it != mComponents.end() ){
        mComponents.erase(it);
    }

}