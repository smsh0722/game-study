#include "AnimSpriteComponent.h"
#include "Actor.h"

AnimSpriteComponent::AnimSpriteComponent( Actor* actor, int drawOrder)
:SpriteComponent(actor, drawOrder),
    mCurrFrame(0.0f),
    mAnimFPS(24.0f)
{
}

void AnimSpriteComponent::Update( float deltaTime )
{
    if ( mAnimTextures.size() > 0 ){
        mCurrFrame += mAnimFPS * deltaTime;

        while ( mCurrFrame > mAnimTextures.size() ){
            mCurrFrame -= mAnimTextures.size();
        }

        SetTexture(mAnimTextures[static_cast<int>(mCurrFrame)]);
    }
}

void AnimSpriteComponent::SetAnimTextures( const std::vector<SDL_Texture*>& textures )
{
    mAnimTextures = textures;
    if ( mAnimTextures.size() > 0 ){
        mCurrFrame = 0.0f;
        SetTexture(mAnimTextures[0]);
    }
}