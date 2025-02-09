#include "SDL2/SDL.h"
#include <vector>
#include <string>
#include <unordered_map>

class Game 
{
public:
    Game();
    bool Initialize();
    void RunLoop();
    void Shutdown();
    
    void AddActor( class Actor* actor );
    void RemoveActor( class Actor* actor );

    void AddSprite( class SpriteComponent* spriteComponent );
    void RemoveSprite( class SpriteComponent* spriteComponent );
    
    SDL_Texture* GetTexture( const std::string& fileName );
private:
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();

    void LoadData();
	void UnloadData();

    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    
    Uint32 mTickCount;

    // Map of textures loaded
	std::unordered_map<std::string, SDL_Texture*> mTextures;

    std::vector<class Actor*> mActors;
    std::vector<class Actor*> mPendingActors;

    std::vector<class SpriteComponent*> mSprites;

    class Ship* mShip;

    bool mIsRunning;
    bool mUpdatingActors;
};