#include "CircleComponent.h"
#include "Actor.h"

CircleComponent::CircleComponent( class Actor* owner, float radius = 0.0f )
: Component(owner)
, mRadius(radius)
{
}

float CircleComponent::GetRadius() const
{
    return mOwner->GetScale() * mRadius;
}

const Vector2& CircleComponent::GetCenter() const
{
    return mOwner->GetPosition();
}

bool CollisionCircle( const CircleComponent& a, const CircleComponent& b )
{
    float ar = a.GetRadius();
    Vector2 ac = a.GetCenter();
    float br = b.GetRadius();
    Vector2 bc = b.GetCenter();
    
    // TIP: sqrt 최대한 피하기
    Vector2 diffVector = ac - bc;
    float diffSq = diffVector.LengthSq();
    float rSumSq = ar + br;
    rSumSq *= rSumSq;

    return diffSq <= rSumSq;
}