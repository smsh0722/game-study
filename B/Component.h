#pragma once

class Component
{
public:
    Component( class Actor* actor, const int mUpdateOrder=100 );
    virtual ~Component();

    virtual void Update(float deltaTime);
    
    int GetUpdateOrder() const { return mUpdateOrder; };
private:
    class Actor* mOwner;
    int mUpdateOrder;
};