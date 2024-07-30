#include "IC_graphicsManager.h"

IC_graphicsManager::IC_graphicsManager()
{
    drawQueue = std::vector<IC_drawable>();
    
    // Camera setup
    cameraPosition = Vector2();
    cameraZoom = 1.0f;
    cameraRotation = 0.0f;
}

void IC_graphicsManager::AddToDrawQueue(IC_drawable drawable)
{
    drawQueue.push_back(drawable);
}

void IC_graphicsManager::Draw()
{
    ClearBackground(BLACK);
    DrawText(TextFormat("Congrats! You created your first window! %f", ((GetRenderWidth() / 1920.0f >= GetRenderHeight() / 1080.0f) ? GetRenderWidth() / 1920.0f : GetRenderHeight() / 1080.0f)), 190, 200, 20, RAYWHITE);

    DrawQueue();
}

void IC_graphicsManager::DrawQueue()
{
    for (auto& drawable : drawQueue) 
    {
        DrawDrawable(drawable);
    }
    drawQueue.clear();
}

void IC_graphicsManager::SetCameraPosition(Vector2 position)
{
    cameraPosition = position;
}

void IC_graphicsManager::SetCameraZoom(float zoom)
{
    cameraZoom = zoom;
}

void IC_graphicsManager::SetCameraRotation(float rotation)
{
    cameraRotation = rotation;
}

float IC_graphicsManager::GetScreenSizeScaling()
{
    return (GetRenderWidth() / 1920.0f >= GetRenderHeight() / 1080.0f) ? GetRenderWidth() / 1920.0f : GetRenderHeight() / 1080.0f;
}

Vector2 IC_graphicsManager::WorldToViewSpace(Vector2 worldPosition)
{
    // Convert to camera position, basically relative to the camera
    Vector2 WorkingPosition = worldPosition * Vec2(1, -1) - cameraPosition * Vec2(1, -1);

    // Zooming
    WorkingPosition = WorkingPosition * cameraZoom;

    // Screen sizing
    // Things scale properly if the window is resized
    WorkingPosition = WorkingPosition * GetScreenSizeScaling();

    // Rotating the position
	WorkingPosition = Vector2Rotate(WorkingPosition, cameraRotation);

    return WorkingPosition;
}

void IC_graphicsManager::DrawDrawable(IC_drawable drawable)
{
    DrawTex(drawable.sprite.texture, WorldToViewSpace(drawable.position), drawable.rotation, drawable.scale * GetScreenSizeScaling(), WHITE);
}