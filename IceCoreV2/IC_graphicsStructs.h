#pragma once

#include <raylib.h>

// A sprite can be anything as simple as a texture to something as complex as an explosion animation
struct IC_sprite
{
public:
    IC_sprite() = default;
    IC_sprite(Texture2D Texture) { texture = Texture; frameWidth = texture.width; frameHeight = texture.height; };
    // Line, row and frame count may not be smaller than 1
    // Frame count may not be larger than line*row
	IC_sprite(Texture2D Texture, int LineCount, int RowCount, int FrameCount)
    {
        texture = Texture; lineCount = LineCount; rowCount = RowCount; frameCount = FrameCount; frameWidth = texture.width / rowCount; frameHeight = texture.height / lineCount; printf(TextFormat("FrameWidth: %f, FrameHeight: %f \n", frameWidth, frameHeight));
    };

    Texture2D texture;

    // Used for sprite sheets
    int lineCount = 1;
    int rowCount = 1;
    int frameCount = 1;

    // Calculated automatically
    float frameWidth = 0.0f;
    // Calculated automatically
    float frameHeight = 0.0f;
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
};