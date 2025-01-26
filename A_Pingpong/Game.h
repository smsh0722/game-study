#pragma once
#include "SDL2/SDL.h"

struct Vector2
{
    float x;
    float y;

    Vector2( float x=0.0f, float y=0.0f ) : x(x), y(y) {}
};

class Object2
{
    public:
        Object2();
        Object2( const Vector2& position, const Vector2& velocity );
        virtual ~Object2() {}

        virtual void UpdatePosition( float deltaTime );
        virtual void Render(SDL_Renderer* renderer);

    protected:
        Vector2 mPosition;
        Vector2 mVelocity;
};

enum PaddleDir{ STAY, UP, DOWN };
class Paddle : public Object2
{
    public:
        Paddle();
        Paddle( const Vector2& position, const Vector2& velocity, float width, float height );

        void SetDirection( PaddleDir paddleDir );
        void UpdatePosition( float deltaTime ) override;
        void Render( SDL_Renderer* renderer ) override;

    private:
        float mWidth;
        float mHeight;
        PaddleDir mPaddleDir;
};

class Ball : public Object2
{
    public:
        Ball();
        Ball( const Vector2& position, const Vector2& velocity, float radius );

        void UpdatePosition( float deltaTime );
        void Render( SDL_Renderer* renderer ) override;
    private:
        float mRadius;
};

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

        Uint32 mTicksCount;

        bool mIsRunning;

        Paddle* mPaddle;
        Ball* mBall;
};