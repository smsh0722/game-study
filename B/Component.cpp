#include "Component.h"
#include "Actor.h"

Component::Component( Actor* owner, const int updateOrder )
    : mOwner(owner),
    mUpdateOrder(updateOrder)
{
    mOwner->AddComponent(this);
}

Component::~Component()
{
    mOwner->RemoveComponent(this);
}

void Component::Update(float deltaTime)
{

}