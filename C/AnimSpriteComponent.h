#pragma once
#include <vector>
#include "SpriteComponent.h"

class AnimSpriteComponent : public SpriteComponent
{
public:
    AnimSpriteComponent( class Actor* owner, int drawOrder=100);
    
    void Update( float deltaTime ) override;
	// Set the textures used for animation
	void SetAnimTextures(const std::vector<SDL_Texture*>& textures);
	// Set/get the animation FPS
	float GetAnimFPS() const { return mAnimFPS; }
	void SetAnimFPS(float fps) { mAnimFPS = fps; }
private:
	// All textures in the animation
	std::vector<SDL_Texture*> mAnimTextures;
	// Current frame displayed
	float mCurrFrame;
	// Animation frame rate
	float mAnimFPS;
};
