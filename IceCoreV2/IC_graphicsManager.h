#pragma once

// Raylib
#include "raylib.h"
#include "raymath.h"

// Standard libraries
#include <vector>

// Other includes
#include "IC_graphicsStructs.h"
#include "VectorHelpers.h"

class IC_graphicsManager
{
public:
    IC_graphicsManager();

private:
    std::vector<IC_drawable> drawQueue;

    Vector2 cameraPosition;
	float cameraZoom;
	float cameraRotation;

public: // Public methods
    void AddToDrawQueue(IC_drawable drawable);
    void Draw();

    // Camera
    void SetCameraPosition(Vector2 position);
    void SetCameraZoom(float zoom);
    void SetCameraRotation(float rotation);
    float GetScreenSizeScaling();
    Vector2 WorldToViewSpace(Vector2 worldPosition);

private: // Private methods
    void DrawDrawable(IC_drawable drawable);
    void DrawTex(Texture2D texture, Vector2 position, float rotation, Vector2 scale, Color tint) // Customized texture drawing function to use Vector2 for scale instead of float
    {
        Rectangle source = { 0.0f, 0.0f, (float)texture.width, (float)texture.height };
        Rectangle dest = { position.x, position.y, (float)texture.width*scale.x, (float)texture.height*scale.y };
        Vector2 origin = { (float)texture.width / 2.f, (float)texture.height / 2.f };

        DrawTexturePro(texture, source, dest, origin, rotation, tint);
    }
    void DrawQueue();
};