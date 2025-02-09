#include "BGSpriteComponent.h"
#include "Actor.h"

BGSpriteComponent::BGSpriteComponent( Actor* actor, int drawOrder )
: SpriteComponent(actor, drawOrder ),
    mScrollSpeed(0)
{
}

void BGSpriteComponent::Update( float deltaTime )
{
    for ( size_t i = 0; i < mBGTextures.size(); i++ ){
        BGTexture& curBGTexture = mBGTextures[i];
        curBGTexture.mOffset.x += mScrollSpeed * deltaTime;
        // 현재 texture가 화면의 더이상 안 나오는지,
        if ( curBGTexture.mOffset.x < -mScreenSize.x){ 
            curBGTexture.mOffset.x = 
                ( mBGTextures.size() - 1 ) * mScreenSize.x - 1;
            // 나머지 화면(size-1) 의 맨 오른쪽으로 다시 이동하여 그려짐
        }
    }
}

void BGSpriteComponent::Draw(SDL_Renderer* renderer )
{
    for ( size_t i = 0; i < mBGTextures.size(); i++ ){
        SDL_Rect rect;
        rect.w = static_cast<int>(mScreenSize.x);
        rect.h = static_cast<int>(mScreenSize.y);
        rect.x = static_cast<int>(
                mOwner->GetPosition().x 
                    - rect.w/2
                         + mBGTextures[i].mOffset.x
                );
        rect.y = static_cast<int>(
                mOwner->GetPosition().y 
                    - rect.h/2
                        + mBGTextures[i].mOffset.y
                );

        SDL_RenderCopy(renderer,
            mBGTextures[i].mTexture,
            nullptr,
            &rect
        );
    }
}

void BGSpriteComponent::SetBGTextures( const std::vector<SDL_Texture*>& textures )
{
    for ( size_t i = 0; i < textures.size(); i++ ){
        BGTexture tmp;
        tmp.mTexture = textures[i];
        tmp.mOffset.x = i * mScreenSize.x;
        tmp.mOffset.y = 0;
        mBGTextures.push_back(tmp);
    }
}