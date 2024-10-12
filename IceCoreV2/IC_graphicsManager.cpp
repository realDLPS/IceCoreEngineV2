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
    //DrawText(TextFormat("Debug stuff %f", 1.0f/GetFrameTime()), 10, 10, 20, RAYWHITE);

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

#pragma region Camera
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
    cameraZoom = Clamp(zoom, 0.001f, 1000.0f);
}

float IC_graphicsManager::GetCameraZoom()
{
    return cameraZoom;
}

void IC_graphicsManager::SetCameraRotation(float rotation)
{
    cameraRotation = fmodf(rotation, 360.0f); // Keeping the values small, if value got too big floating point errors might cause problems.
}

float IC_graphicsManager::GetCameraRotation()
{
    return cameraRotation;
}
#pragma endregion

#pragma region Viewport
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

    // Rotating the position (and going from degrees to radians)
    WorkingPosition = Vector2Rotate(WorkingPosition, cameraRotation * 0.0174533f);

    return WorkingPosition + Vec2(float(GetScreenWidth()) / 2.0f, float(GetScreenHeight()) / 2.0f);
}
#pragma endregion

void IC_graphicsManager::DrawDrawable(IC_drawable drawable)
{
    Rectangle frame = Rectangle();
    frame.width = drawable.sprite.frameWidth;
	frame.height = drawable.sprite.frameHeight;
    
    
    // Scaling to account for multiple frames in a single texture
    float xScale = frame.width / drawable.sprite.texture.width;
	float yScale = frame.height / drawable.sprite.texture.height;

    // This can be redone to support differently sorted sprite sheets
    // Currently frames are expected to be sorted in the way shown below
    // 0 1 2
    // 3 4 5
    // 6 7 8
    int x = drawable.frame % drawable.sprite.rowCount;
	int y = drawable.frame / drawable.sprite.rowCount;
	frame.x = x * drawable.sprite.frameWidth;
	frame.y = y * drawable.sprite.frameHeight;

    DrawTex(
        drawable.sprite.texture, 
        frame, 
        WorldToViewSpace(drawable.position), 
        drawable.rotation + cameraRotation,
        drawable.scale * GetScreenSizeScaling() * cameraZoom * Vec2(xScale, yScale), 
        WHITE);
}