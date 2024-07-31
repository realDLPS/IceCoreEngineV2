#pragma once

// Raylib
#include "raylib.h"
#include "raymath.h"

// Standard libraries
#include <vector>

// Other includes
#include "IC_graphicsStructs.h"
#include "vectorHelpers.h"

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
    Vector2 GetCameraPosition();
    void SetCameraZoom(float zoom);
	float GetCameraZoom();
    void SetCameraRotation(float rotation);
	float GetCameraRotation();


    // Viewport
    float GetScreenSizeScaling();
    Vector2 WorldToViewSpace(Vector2 worldPosition);

private: // Private methods
    void DrawDrawable(IC_drawable drawable);
    void DrawTex(Texture2D texture, Rectangle frame, Vector2 position, float rotation, Vector2 scale, Color tint) // Customized texture drawing function to use Vector2 for scale instead of float
    {
        Rectangle dest = { position.x, position.y, (float)texture.width*scale.x, (float)texture.height*scale.y };

        DrawTexturePro(texture, frame, dest, Vec2(dest.width / 2, dest.height / 2), rotation, tint);
    }
    void DrawQueue();
};