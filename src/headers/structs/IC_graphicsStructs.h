#pragma once

#include <raylib.h>

struct IC_sprite
{
    IC_sprite();

    Texture2D texture;
};

struct IC_drawable
{
    IC_drawable();

    IC_sprite sprite;
    Vector2 position;
    Vector2 scale;
    float rotation;
};