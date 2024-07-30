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
    DrawText(TextFormat("Debug stuff %f", ((GetRenderWidth() / 1920.0f >= GetRenderHeight() / 1080.0f) ? GetRenderWidth() / 1920.0f : GetRenderHeight() / 1080.0f)), 10, 10, 20, RAYWHITE);

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

Vector2 IC_graphicsManager::GetCameraPosition()
{
    return cameraPosition;
}

void IC_graphicsManager::SetCameraZoom(float zoom)
{
    cameraZoom = zoom;
}

float IC_graphicsManager::GetCameraZoom()
{
    return cameraZoom;
}

void IC_graphicsManager::SetCameraRotation(float rotation)
{
    cameraRotation = rotation;
}

float IC_graphicsManager::GetCameraRotation()
{
    return cameraRotation;
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

    return WorkingPosition + Vec2(GetScreenWidth() / 2, GetScreenHeight() / 2);
}

void IC_graphicsManager::DrawDrawable(IC_drawable drawable)
{
    Rectangle frame = Rectangle();
    frame.width = drawable.sprite.frameWidth;
	frame.height = drawable.sprite.frameHeight;
    // This can be redone to support differently sorted sprite sheets
    // Currently frames are expected to be sorted in the way shown below
    // 0 1 2
	// 3 4 5
	// 6 7 8
    
    float xScale = frame.width / drawable.sprite.texture.width;
	float yScale = frame.height / drawable.sprite.texture.height;

    int x = drawable.frame % drawable.sprite.rowCount;
	int y = drawable.frame / drawable.sprite.rowCount;
	frame.x = x * drawable.sprite.frameWidth;
	frame.y = y * drawable.sprite.frameHeight;

    DrawTex(drawable.sprite.texture, frame, WorldToViewSpace(drawable.position) - (Vec2(frame.width / 2, frame.height / 2) * GetScreenSizeScaling() * cameraZoom), drawable.rotation, drawable.scale * GetScreenSizeScaling() * cameraZoom * Vec2(xScale, yScale), WHITE);
}