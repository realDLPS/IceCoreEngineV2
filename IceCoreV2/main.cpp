/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute raylib_compile_execute script
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   Example originally created with raylib 1.0, last time updated with raylib 1.0
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2013-2024 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include "IC_graphicsManager.h"
#include "VectorHelpers.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 450;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "IceCoreEngineV2");

    SetTargetFPS(120);

    float TimeSinceGameStart = 0.f;

    // IceCore classes
    IC_graphicsManager graphicsManager = IC_graphicsManager();



    Texture2D circle = LoadTexture("../Assets/Circle.png");
    Texture2D explosion = LoadTexture("../Assets/Explosion.png");
    IC_sprite explosionSprite = IC_sprite(explosion, 4, 4, 16);
    Texture2D fire = LoadTexture("../Assets/Fire.png");
    IC_sprite fireSprite = IC_sprite(fire, 1, 25, 25);
    Texture2D smoke = LoadTexture("../Assets/Smoke.png");
    IC_sprite smokeSprite = IC_sprite(smoke, 7, 7, 45);

    while (!WindowShouldClose())
    {
        TimeSinceGameStart += GetFrameTime();

        graphicsManager.AddToDrawQueue(IC_drawable(IC_sprite(circle), Vec2(0), Vec2(1.f), 0.f));

        graphicsManager.AddToDrawQueue(IC_drawable(explosionSprite, Vec2(-200.f, 200.f), Vec2(1.f), 0.0f, int(TimeSinceGameStart*32) % 16));

        graphicsManager.AddToDrawQueue(IC_drawable(fireSprite, Vec2(-200.f), Vec2(1.f), 0.0f, int(TimeSinceGameStart * 24) % 25));

        graphicsManager.AddToDrawQueue(IC_drawable(smokeSprite, Vec2(200.f), Vec2(1.f), 0.0f, int(TimeSinceGameStart * 24) % 45));

        graphicsManager.SetCameraZoom(graphicsManager.GetCameraZoom() + GetMouseWheelMove() * 0.2f);
        
        BeginDrawing();

        graphicsManager.Draw();

        EndDrawing();
    }

    UnloadTexture(circle);
    CloseWindow();
    return 0;
}