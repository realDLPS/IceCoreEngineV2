#include "IC_exampleGame.h"

#include "IC_uiButton.h"
#include "IC_uiText.h"

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

    GfxMgr()->SetCameraZoom(GfxMgr()->GetCameraZoom() + InpSys()->GetAxisValue("Zoom"));
    GfxMgr()->SetCameraRotation(GfxMgr()->GetCameraRotation() + InpSys()->GetAxisValue("Rotate") * -1.0f);
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
    IC_mapping rotate = IC_mapping({ IC_binding(MOUSE_AXIS_X, 0.05f), IC_binding(GAMEPAD_AXIS_RIGHT_X, 180.0f, true), IC_binding(KEY_RIGHT, 180.0f, true), IC_binding(KEY_LEFT, -180.0f, true) });

    GetInputSystem()->AddMapping("Rotate", rotate, true);

    // Showing cursor
    IC_mapping showCursor = IC_mapping({ IC_binding(KEY_C, 1.0f) });
    showCursor.AddDelegate(IC_delegate(ToggleCursor));

    GetInputSystem()->AddMapping("ShowCursor", showCursor, false);

    // Zooming
    IC_mapping zoom = IC_mapping(IC_binding(0, 0.2f, false));
    GetInputSystem()->AddMapping("Zoom", zoom, true);
#pragma endregion

    explosionSprite = IC_sprite(Tex("Explosion"), 4, 4, 16);
    fireSprite = IC_sprite(Tex("Fire"), 1, 25, 25);
    smokeSprite = IC_sprite(Tex("Smoke"), 7, 7, 45);
    SetTextureFilter(Tex("Smoke"), TEXTURE_FILTER_BILINEAR); // Fairly reasonable way to set filtering

    ICPrint(IC_debugString("Hello", 5.0f, RED), false);

    // Very painful way of creating a "button", it really isn't a button yet, but hey it renders!
    IC_uiButton* testButton = ObjSys()->SpawnObject<IC_uiButton>(true, true, 1.0f / 60.0f, true, false);
    testButton->Anchor = IC_uiAlignment::TopCenter;
    testButton->Alignment = IC_uiAlignment::TopCenter;
    testButton->Scaling = IC_uiScaling::LiteralScaled;
    testButton->Offset = Vec2(0, 10);
    testButton->Scale = Vec2(500, 200);
    testButton->EnableAutoDraw();
    ObjSys()->FinishSpawn(testButton->GetId(), true);

    // Creating a child button that will be attached to the parent button
    IC_uiButton* testChildButton = ObjSys()->SpawnObject<IC_uiButton>(true, true, 1.0f / 60.0f, true, false);
    testChildButton->Anchor = IC_uiAlignment::BottomCenter;
    testChildButton->Alignment = IC_uiAlignment::TopCenter;
    testChildButton->Scaling = IC_uiScaling::Relative;
    testChildButton->Offset = Vec2(0, 10);
    testChildButton->Scale = Vec2(0.75f, 0.3f);
    testChildButton->EnableAutoDraw();
	ObjSys()->FinishSpawn(testChildButton->GetId(), true);

    testButton->AddChild(testChildButton);
    
    // Creating some text
    IC_uiText* testText = ObjSys()->SpawnObject<IC_uiText>(true, true, 1.0f / 60.0f, true, false);
	testText->Anchor = IC_uiAlignment::Center;
	testText->Alignment = IC_uiAlignment::Center;
	testText->Scaling = IC_uiScaling::LiteralScaled;
	testText->Offset = Vec2(0, 0);
	testText->Scale = Vec2(0);
	testText->EnableAutoDraw();
    testText->Text = "Testing";
    testText->FontSize = 125;
    testText->Spacing = 2;
	ObjSys()->FinishSpawn(testText->GetId(), true);

    testButton->AddChild(testText);

    HideCursor();
    DisableCursor();
    SetTargetFPS(500);
}

void IC_exampleGame::EndPlay()
{

}

void IC_exampleGame::DrawUI(float deltaTime)
{
    // Bare minimum, going to be moved into the specific UI classes later
    nk_begin(nkCtx, "Test", nk_rect(50, 50, GetScreenWidth()/5.f, GetScreenHeight()/5.f), NK_WINDOW_NO_SCROLLBAR);
    nk_layout_row_dynamic(nkCtx, 100, 1);

    // Here you can see usage of the TEXTc macro
    // See TEXTcCache macro in use below
    nk_style_set_font(nkCtx, ICFONT("Roboto", 48.0f * (std::sin(GetTime())+5.f) / 6.f)); // Example of font size changing dynamically
    if (nk_button_label(nkCtx, TEXTc("TestLabel")))
    {
        game->GetLocalisationSystem()->SetLocale(game->GetLocalisationSystem()->GetLocale() == "en" ? "fi" : "en");
    }
    nk_end(nkCtx);

    nk_begin(nkCtx, "Test2", nk_rect(50, 65 + GetScreenHeight() / 5.f, GetScreenWidth() / 5.f, GetScreenHeight() / 3.f), NK_WINDOW_NO_SCROLLBAR);
    nk_layout_row_dynamic(nkCtx, 300, 1);

    // And here is usage of the TEXTcCache macro
    // In my quick testing this is roughly 3x faster than just constantly calling TEXTc
    TEXTcCache("TestText", testText)
    nk_style_set_font(nkCtx, ICFONT("Roboto", 18.0f));
    nk_label_wrap(nkCtx, testText);
    nk_end(nkCtx);
}
