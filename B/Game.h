#include "SDL2/SDL.h"
#include <vector>

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
private:
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();

    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    Uint32 mTickCount;
    bool mIsRunning;

    std::vector<class Actor*> mActors;
    std::vector<class Actor*> mPendingActors;

    std::vector<class SpriteComponent*> mSprites;

    class Ship* ship;

    bool mUpdatingActors;
};