#pragma once
#include "Component.h"

class SpriteComponent : public Component
{
public:
    SpriteComponent();

    void Update( float deltaTime ) override;
    
private:
};