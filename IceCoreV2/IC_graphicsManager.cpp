#include "IC_graphicsManager.h"

IC_graphicsManager::IC_graphicsManager()
{
    drawQueue = std::vector<IC_drawable>();
    
    // Camera setup
    camera = Camera2D();
    camera.offset = Vector2{0.0f, 0.0f};
    camera.target = Vector2{0.0f, 0.0f};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
}

void IC_graphicsManager::AddToDrawQueue(IC_drawable drawable)
{
    drawQueue.push_back(drawable);
}

void IC_graphicsManager::DrawQueue()
{
    for (auto& drawable : drawQueue) 
    {
        Draw(drawable);
    }
    drawQueue.clear();
}

void IC_graphicsManager::SetCameraPosition(Vector2 position)
{
    camera.target = position;
}

void IC_graphicsManager::SetCameraZoom(float zoom)
{
    camera.zoom = zoom;
}

void IC_graphicsManager::SetCameraRotation(float rotation)
{
    camera.rotation = rotation;
}

void IC_graphicsManager::Draw(IC_drawable drawable)
{
    DrawTex(drawable.sprite.texture, GetWorldToScreen2D(drawable.position, camera), drawable.rotation, drawable.scale, WHITE);
}