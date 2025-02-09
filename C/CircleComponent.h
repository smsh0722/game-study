#pragma once
#include "Component.h"
#include "Math.h"

class CircleComponent : public Component
{
public:
    CircleComponent(class Actor* owner, float radius = 0.0f );

    // Getter, Setter
    float GetRadius() const ;
    const Vector2& GetCenter() const ;
    void SetRadius( const float radius ) { mRadius = radius; };
private:
    float mRadius;
};

bool CollisionCircle( const CircleComponent& a, const CircleComponent& b );