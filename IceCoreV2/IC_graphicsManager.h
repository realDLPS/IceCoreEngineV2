#pragma once

// Raylib
#include "raylib.h"

// Standard libraries
#include <vector>

// Other includes
#include "IC_graphicsStructs.h"

class IC_graphicsManager
{
public:
    IC_graphicsManager();

private:
    std::vector<IC_drawable> drawQueue;
    Camera2D camera;

public: // Public methods
    void AddToDrawQueue(IC_drawable drawable);
    void DrawQueue();

    void SetCameraPosition(Vector2 position);
    void SetCameraZoom(float zoom);
    void SetCameraRotation(float rotation);

private: // Private methods
    void Draw(IC_drawable drawable);
    void DrawTex(Texture2D texture, Vector2 position, float rotation, Vector2 scale, Color tint) // Customized texture drawing function to use Vector2 for scale instead of float
    {
        Rectangle source = { 0.0f, 0.0f, (float)texture.width, (float)texture.height };
        Rectangle dest = { position.x, position.y, (float)texture.width*scale.x, (float)texture.height*scale.y };
        Vector2 origin = { 0.0f, 0.0f };

        DrawTexturePro(texture, source, dest, origin, rotation, tint);
    }
};