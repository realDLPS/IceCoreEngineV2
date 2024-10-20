#include "IC_exampleGame.h"

bool IC_exampleGame::ToggleCursor(float value)
{
    if (value == 1.0f) // Is this a press?
    {
        if (IsCursorHidden())
        {
            ShowCursor();
            EnableCursor();
        }
        else
        {
            HideCursor();
            DisableCursor();
        }
    }
    return true; // Consume the input
}

void IC_exampleGame::Tick(float deltaTime)
{
    ICPrint(IC_debugString(std::string("FPS: ") + std::to_string(GetFPS()), 0.0f), false);
    ICPrint(IC_debugString(std::string("Camera rotation: ") + std::to_string(GfxMgr()->GetCameraRotation()), 0.0f), false);

    GfxMgr()->AddToDrawQueue(IC_drawable(IC_sprite(Tex("Circle")), Vec2(0), Vec2(1.f), 0.f));
    GfxMgr()->AddToDrawQueue(IC_drawable(explosionSprite, Vec2(-200.f, 200.f), Vec2(1.f), 0.0f, int(GetTime() * 32) % 16));
    GfxMgr()->AddToDrawQueue(IC_drawable(fireSprite, Vec2(-200.f), Vec2(1.f), 0.0f, int(GetTime() * 24) % 25));
    GfxMgr()->AddToDrawQueue(IC_drawable(smokeSprite, Vec2(200.f), Vec2(1.f), 0.0f, int(GetTime() * 24) % 45));

    GfxMgr()->SetCameraZoom(GfxMgr()->GetCameraZoom() + GetMouseWheelMove() * 0.2f);
    GfxMgr()->SetCameraRotation(GfxMgr()->GetCameraRotation() + InpSys()->GetAxisValue("Rotate") * -0.03f);
    GfxMgr()->SetCameraPosition(GfxMgr()->GetCameraPosition() + rotVec2(Vector2Normalize(Vec2(InpSys()->GetAxisValue("MoveRight"), InpSys()->GetAxisValue("MoveUp"))), GfxMgr()->GetCameraRotation()) * 300.0f * GetFrameTime());
}

void IC_exampleGame::BeginPlay()
{
#pragma region Input mappings
    // Movement
    IC_mapping moveUp = IC_mapping({ IC_binding(KEY_W, 1.0f), IC_binding(KEY_S, -1.0f), IC_binding(GAMEPAD_AXIS_LEFT_Y, -1.0f) });
    IC_mapping moveRight = IC_mapping({ IC_binding(KEY_D, 1.0f), IC_binding(KEY_A, -1.0f), IC_binding(GAMEPAD_AXIS_LEFT_X, 1.0f) });

    // Some getters have abbreviations available.
    // GetInputSystem() and InpSys() return the same pointer.
    GetInputSystem()->AddMapping("MoveUp", moveUp, true);
    InpSys()->AddMapping("MoveRight", moveRight, true);


    // Rotation
    IC_mapping rotate = IC_mapping({ IC_binding(MOUSE_AXIS_X, 1.0f), IC_binding(GAMEPAD_AXIS_RIGHT_X, 25.0f), IC_binding(KEY_RIGHT, 15.0f), IC_binding(KEY_LEFT, -15.0f) });

    GetInputSystem()->AddMapping("Rotate", rotate, true);

    // Showing cursor
    IC_mapping showCursor = IC_mapping({ IC_binding(KEY_C, 1.0f) });
    showCursor.AddDelegate(std::bind_front(&IC_exampleGame::ToggleCursor, this));

    GetInputSystem()->AddMapping("ShowCursor", showCursor, false);
#pragma endregion

    explosionSprite = IC_sprite(Tex("Explosion"), 4, 4, 16);
    fireSprite = IC_sprite(Tex("Fire"), 1, 25, 25);
    smokeSprite = IC_sprite(Tex("Smoke"), 7, 7, 45);

    ICPrint(IC_debugString("Hello", 5.0f, RED), false);

    HideCursor();
    DisableCursor();
}

void IC_exampleGame::EndPlay()
{

}
