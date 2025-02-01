#include "Component.h"
#include "Actor.h"

Component::Component( class Actor* actor, const int updateOrder )
    : mOwner(actor),
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