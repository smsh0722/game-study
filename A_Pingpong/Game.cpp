#include "Game.h"
#include <iostream>

const float paddleVelY = 300.0f;
const int thickness = 15;
const float paddleH = 100.0f;
const int winW = 1024;
const int winH = 768;

Game::Game()
{
    mWindow = nullptr;
    mRenderer = nullptr;
    mTicksCount = 0;
    mIsRunning = true;
    mPaddle1 = nullptr;
    mPaddle2 = nullptr;
    mBall = nullptr;
}

bool Game::Initialize()
{   
    // Init SDL
    bool sdlInitRst = SDL_Init( SDL_INIT_VIDEO );
    if ( sdlInitRst != 0 ){
        SDL_Log("Unable to init sdl: %s", SDL_GetError() );
        return false;
    }

    // Create a SDL window
    mWindow = SDL_CreateWindow(
        "PingPong",
        100,
        100,
        winW,
        winH,
        0
    );
    if ( mWindow == NULL ){
        SDL_Log( "Fail to create window: %s", SDL_GetError() );
        return false;
    }

    // Create SDL Renderer
    mRenderer = SDL_CreateRenderer(
        mWindow,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );
    if ( mRenderer == NULL ){
        SDL_Log( "Failed to create SDL RENDERER: %s", SDL_GetError() );
        return false;
    }

    // Create mPaddle1
    mPaddle1 = new Paddle( Vector2{10.0f, winH/2.0f}, 
                            Vector2{0.0f, 300.0f},
                            thickness,
                            100.0f );
    if ( mPaddle1 == nullptr ){
        return false;
    }

    // Create mPaddle2
    mPaddle2 = new Paddle( Vector2{winW-10.0f-thickness, winH/2.0f},
                            Vector2{0.0f, 300.0f},
                            thickness,
                            100.0f );
    if ( mPaddle2 == nullptr ){
        return false;
    }

    // Create mBall
    mBall = new Ball( Vector2{winW/2.0f, winH/2.0f}, Vector2{-200.0f, 235.0f}, 15.0f );
    if ( mBall == nullptr ){
        return false;
    }

    return true;
}

void Game::RunLoop()
{
    while (mIsRunning == true ){
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

void Game::Shutdown()
{
    if ( mPaddle1 != nullptr ){
        delete mPaddle1;
        mPaddle1 = nullptr;
    }
    if ( mPaddle2 != nullptr ){
        delete mPaddle2;
        mPaddle2 = nullptr;
    }
    if ( mBall != nullptr ){
        delete mBall;
        mBall = nullptr;
    }
    
    SDL_DestroyRenderer( mRenderer );
    SDL_DestroyWindow( mWindow );
    SDL_Quit();
}

void Game::ProcessInput()
{   
    // Check Quit event
    SDL_Event event;
    while ( SDL_PollEvent(&event) ){
        switch(event.type){
            case SDL_QUIT:
                mIsRunning = false;
                break;
        }
    }

    // Check Escape input
    const Uint8* state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_ESCAPE] ){
        mIsRunning = false;
    }

    // Set Paddle direction
    mPaddle1->SetDirection(STAY);
    if ( state[SDL_SCANCODE_W] ){ // UP
        mPaddle1->SetDirection(UP);
    }
    else if ( state[SDL_SCANCODE_S] ){ // Down
        mPaddle1->SetDirection(DOWN);
    }

    mPaddle2->SetDirection(STAY);
    if ( state[SDL_SCANCODE_UP] ){
        mPaddle2->SetDirection(UP);
    }
    else if ( state[SDL_SCANCODE_DOWN] ){
        mPaddle2->SetDirection(DOWN);
    }
}

void Game::UpdateGame()
{   
    // max 60fps
    while( SDL_TICKS_PASSED( SDL_GetTicks(), mTicksCount+16) == false ){
        ;
    }

    // difference from last frame (sec)
    float deltaTime = ( SDL_GetTicks() - mTicksCount ) / 1000.0f;
    
    // limit delta time 
    if ( deltaTime > 0.05f )
    {
        deltaTime = 0.05f;
    }
    
    // Renew mTicks 
    mTicksCount = SDL_GetTicks();

    // update paddle1 position
    mPaddle1->UpdatePosition( deltaTime );

    // update paddle2 position
    mPaddle2->UpdatePosition( deltaTime );

    // update ball position
    mBall->UpdatePosition( deltaTime, *mPaddle1, *mPaddle2 );
}

void Game::GenerateOutput()
{
    // Set Black 
    SDL_SetRenderDrawColor(
        mRenderer,
        0, 0, 0, 255 // R, G, B, A
    );

    SDL_RenderClear(mRenderer);

    // Set white
    SDL_SetRenderDrawColor( mRenderer, 255, 255, 255, 255 );
    SDL_Rect tWall { 0, 0, winW, thickness };
    //SDL_Rect rWall { winW - thickness, 0, thickness, winH };
    SDL_Rect bWall { 0, winH-thickness, winW, thickness };
    SDL_RenderFillRect(mRenderer, &tWall);
    //SDL_RenderFillRect(mRenderer, &rWall);
    SDL_RenderFillRect(mRenderer, &bWall);

    // Draw paddle
    mPaddle1->Render(mRenderer);
    mPaddle2->Render(mRenderer);
    
    // Draw ball
    mBall->Render(mRenderer);

    // Swap front buffer and back buffer
    SDL_RenderPresent( mRenderer);
}

Object2::Object2() : mPosition(0.0f, 0.0f), mVelocity(0.0f, 0.0f) {}

Object2::Object2( const Vector2& position, const Vector2& velocity )
{
    mPosition = position;
    mVelocity = velocity;
}

void Object2::UpdatePosition( float deltaTime )
{
    mPosition.x += mVelocity.x*deltaTime;
    mPosition.y += mVelocity.y*deltaTime;
}

void Object2::Render( SDL_Renderer* renderer )
{
}

Vector2 Object2::getPosition()
{
    return mPosition;
}

Paddle::Paddle( const Vector2& position, const Vector2& velocity, float width, float height )
{
    mPosition = position;
    mVelocity = velocity;
    mWidth = width;
    mHeight = height;
    mPaddleDir = STAY;
}

void Paddle::SetDirection( PaddleDir paddleDir )
{
    mPaddleDir = paddleDir;
}

void Paddle::UpdatePosition( float deltaTime )
{
    // Move Position
    if ( mPaddleDir == UP ){
        mPosition.y -= mVelocity.y * deltaTime;
    }
    else if ( mPaddleDir == DOWN ){
        mPosition.y += mVelocity.y * deltaTime; 
    }

    // Check range
    if ( mPosition.y < thickness ){
        mPosition.y = thickness;
    }
    else if ( mPosition.y > (winH - thickness - mHeight) ){
        mPosition.y = winH - thickness - mHeight;
    }
}

void Paddle::Render( SDL_Renderer* renderer )
{
    // Set green
    SDL_SetRenderDrawColor( renderer, 0, 100, 0, 255 );
    SDL_Rect paddle {
        static_cast<int>(mPosition.x),
        static_cast<int>(mPosition.y),
        static_cast<int>(mWidth),
        static_cast<int>(mHeight)
    };
    SDL_RenderFillRect( renderer, &paddle );
}

float Paddle::getWidth()
{
    return mWidth;
}

float Paddle::getHeight()
{
    return mHeight;
}


Ball:: Ball( const Vector2& position, const Vector2& velocity, float radius )
{
    mPosition = position;
    mVelocity = velocity;
    mRadius = radius;
}

void Ball::UpdatePosition( float deltaTime, Paddle& paddle1, Paddle& paddle2 )
{
    // Move
    mPosition.x += mVelocity.x * deltaTime;
    mPosition.y += mVelocity.y * deltaTime;

    // Bounce
    // Check collision with top or bottom wall
    if ( mPosition.y <= thickness && mVelocity.y < 0.0f ){
        mVelocity.y *= -1;
    }
    else if ( mPosition.y >= (winH - thickness - mRadius) && mVelocity.y > 0.0f ){
        mVelocity.y *= -1;
    }

    // Check collision with right wall
    /*
    if ( mPosition.x >= ( winW - thickness - mRadius) && mVelocity.x > 0.0f ){
        mVelocity.x *= -1;
    }*/

    // Check collision with paddle1
    {
        Vector2 paddlePos = paddle1.getPosition();
        float paddleW = paddle1.getWidth();
        float paddleH = paddle1.getHeight();
        if( mPosition.x <= ( paddlePos.x + paddleW ) ){
            if ( (paddlePos.y - mRadius) < mPosition.y &&
                            mPosition.y < (paddlePos.y + paddleH +mRadius ) ){
                if ( mVelocity.x < 0.0f ){
                    mVelocity.x *= -1;
                }
            }
        }
    }

    // Check collision with paddle2
    {
        Vector2 paddlePos = paddle2.getPosition();
        float paddleH = paddle2.getHeight();
        if( mPosition.x >= (paddlePos.x-mRadius) ){
            if ( (paddlePos.y - mRadius) < mPosition.y &&
                            mPosition.y < (paddlePos.y + paddleH +mRadius ) ){
                if ( mVelocity.x > 0.0f ){
                    mVelocity.x *= -1;
                }
            }
        }
    }   
}

void Ball::Render( SDL_Renderer* renderer )
{
    // Set white
    SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );

    SDL_Rect ball {
        static_cast<int>(mPosition.x),
        static_cast<int>(mPosition.y),
        static_cast<int>(mRadius),
        static_cast<int>(mRadius)
    };

    SDL_RenderFillRect( renderer, &ball );
}