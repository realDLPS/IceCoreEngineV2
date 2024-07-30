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

    // IceCore classes
    IC_graphicsManager graphicsManager = IC_graphicsManager();

    Texture2D circle = LoadTexture("../Assets/circle.png");

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        graphicsManager.AddToDrawQueue(IC_drawable(IC_sprite(circle), Vec2(960, -540), 1.f, 0.f));


        
        BeginDrawing();

        graphicsManager.Draw();

        EndDrawing();
    }

    UnloadTexture(circle);

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}