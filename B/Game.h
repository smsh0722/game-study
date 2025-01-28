#include "SDL2/SDL.h"
#include <vector>

class Game 
{
public:
    Game();
    bool Initialize();
    void RunLoop();
    void Shutdown();
private:
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();

    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    Uint32 mTickCount;
    bool mIsRunning;

    std::vector<class Actor*> mActors;
    std::vector<class SpritesComponent*> mSprites;
    class ship* ship;
};