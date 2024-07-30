#pragma once

#include <raylib.h>

struct IC_sprite
{
public:
    IC_sprite() = default;
    IC_sprite(Texture2D Texture) { texture = Texture; };

    Texture2D texture;
};

struct IC_drawable
{
public:
    IC_drawable() = default;

    IC_drawable(IC_sprite Sprite) { sprite = Sprite; };

    IC_drawable(IC_sprite Sprite, Vector2 Position) { sprite = Sprite; position = Position; };

    IC_drawable(IC_sprite Sprite, Vector2 Position, Vector2 Scale) 
    { sprite = Sprite; position = Position; scale = Scale; };

    IC_drawable(IC_sprite Sprite, Vector2 Position, float Rotation) 
    { sprite = Sprite; position = Position; rotation = Rotation; };
    
    IC_drawable(IC_sprite Sprite, Vector2 Position, Vector2 Scale, float Rotation) 
    { sprite = Sprite; position = Position; scale = Scale; rotation = Rotation; };

    IC_drawable(IC_sprite Sprite, Vector2 Position, float Scale, float Rotation)
    {
        sprite = Sprite; position = Position; scale.x = Scale; scale.y = Scale; rotation = Rotation;
    };

    IC_sprite sprite = IC_sprite();
    Vector2 position = Vector2();
    Vector2 scale = Vector2();
    float rotation = 0.0f;
};