#pragma once
#include <vector>
#include "math.h"

class Actor
{
public:
    enum State
    {
        EAlive, EDead, EPaused
    };

    Actor( class Game* game );
    virtual ~Actor();

    void Update(float deltaTime);
    void UpdateComponents(float deltaTime);
    void UpdateActor(float deltaTime);
    
    // Getter/ Setter
    const Vector2& GetPosition() const { return mPosition; }
    void SetPosition( const Vector2& position) { mPosition = position; }
    float GetScale() const { return mScale; }
    void SetScale( float scale ) { mScale=scale; }
    float GetRotation() const {return mRotation; }
    void SetRotation( float rotation ) { mRotation=rotation; }
    State GetState() const { return mState; }
    void SetState( State state ){ mState = state; }
    class Game* GetGame() { return mGame; }
    
    // Add/reomove component
    void AddComponent( class Component* component );
    void RemoveComponent( class Component* component );    
private:
    State mState;

    Vector2 mPosition;
    float mScale;
    float mRotation;

    std::vector<class Component*> mComponents;
    class Game* mGame;
};