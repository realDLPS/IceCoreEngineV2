#include "IC_uiPrimitives.h"

void IC_uiCanvas::Draw(float deltaTime)
{
	nkCtx->style.window.fixed_background = nk_style_item_color(nk_rgba(0, 0, 0, 0));
	nk_begin(nkCtx, "", nk_rect(position.x, position.y, size.x, size.y), NK_WINDOW_BACKGROUND | NK_WINDOW_NO_SCROLLBAR);
	
	DrawChildren(deltaTime);

	nk_end(nkCtx);
}
