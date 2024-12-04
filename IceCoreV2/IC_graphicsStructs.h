#pragma once

#include <raylib.h>

// A sprite can be anything as simple as a texture to something as complex as an explosion animation
struct IC_sprite
{
public:
    IC_sprite() = default;
    IC_sprite(Texture2D Texture) { texture = Texture; frameWidth = float(texture.width); frameHeight = float(texture.height); };
    // Line, row and frame count may not be smaller than 1
    // Frame count may not be larger than line*row
	IC_sprite(Texture2D Texture, int LineCount, int RowCount, int FrameCount, bool worldSpace = true)
    {
        texture = Texture; lineCount = LineCount; rowCount = RowCount; frameCount = FrameCount; frameWidth = float(texture.width) / float(rowCount); frameHeight = float(texture.height) / float(lineCount); printf(TextFormat("FrameWidth: %f, FrameHeight: %f \n", frameWidth, frameHeight));
    };

    Texture2D texture = Texture2D();

    // Used for sprite sheets
    int lineCount = 1;
    int rowCount = 1;
    int frameCount = 1;

    // Calculated automatically
    float frameWidth = 0.0f;
    // Calculated automatically
    float frameHeight = 0.0f;

    // Used for better scaling
    // For example can keep button corners from streching.
    bool UseSlicing = false;
    int SlicingType = 0; // 0 = 3x3, 1 = 1x3, 2 = 3x1
    int Left = 0;
    int Top = 0;
    int Right = 0;
    int Bottom = 0;
};

struct IC_drawable
{
public:

    #pragma region Constructors
    IC_drawable() = default;

    IC_drawable(IC_sprite Sprite) { sprite = Sprite; };

    IC_drawable(IC_sprite Sprite, Vector2 Position) { sprite = Sprite; position = Position; };

    IC_drawable(IC_sprite Sprite, Vector2 Position, Vector2 Scale)
    {
        sprite = Sprite; position = Position; scale = Scale;
    };

    IC_drawable(IC_sprite Sprite, Vector2 Position, float Rotation)
    {
        sprite = Sprite; position = Position; rotation = Rotation;
    };

    IC_drawable(IC_sprite Sprite, Vector2 Position, Vector2 Scale, float Rotation)
    {
        sprite = Sprite; position = Position; scale = Scale; rotation = Rotation;
    };

    IC_drawable(IC_sprite Sprite, Vector2 Position, Vector2 Scale, float Rotation, int Frame)
    {
        sprite = Sprite; position = Position; scale = Scale; rotation = Rotation; frame = Frame;
    };
#pragma endregion

    IC_sprite sprite = IC_sprite();
    Vector2 position = Vector2();
    Vector2 scale = Vector2();
    float rotation = 0.0f;
    int frame = 0;
    bool worldSpace = true;
};

struct IC_uiStyle
{
public:
    IC_uiStyle() {};

	Color backgroundColor = Color{ 0, 0, 0, 0 };
	Color borderColor = Color{ 0, 0, 0, 0 };
	Color textColor = Color{ 0, 0, 0, 0 };

    IC_sprite button = IC_sprite();

    Font font = Font();
};