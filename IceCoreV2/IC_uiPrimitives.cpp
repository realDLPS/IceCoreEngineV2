#include "IC_uiPrimitives.h"

#define EMPTYTICK Tick(float deltaTime){}
#define EMPTYBEGINPLAY BeginPlay(){}
#define EMPTYENDPLAY EndPlay(){}

// Creates the tick, begin play and end play functions for a class quickly
#define EMPTYOBJFUNCS(classname) void classname::EMPTYTICK void classname::EMPTYBEGINPLAY void classname::EMPTYENDPLAY

void IC_uiCanvas::Draw(float deltaTime)
{
	nk_layout_space_begin(nkCtx, NK_STATIC, size.y, Children.size());

	nk_layout_space_push(nkCtx, nk_rect(position.x, position.y, size.x, size.y));

	DrawChildren(deltaTime);

	nk_layout_space_end(nkCtx);

	nk_begin(nkCtx, "", nk_rect(position.x, position.y, size.x, size.y), NK_WINDOW_BACKGROUND | NK_WINDOW_NO_SCROLLBAR);
	
	
	
	nk_end(nkCtx);
}
EMPTYOBJFUNCS(IC_uiCanvas)