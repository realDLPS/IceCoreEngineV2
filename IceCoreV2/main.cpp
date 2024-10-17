// Examples
#include "IC_exampleGame.h"

#ifndef _DEBUG

#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#endif


int main(void)
{
    IC_exampleGame game = IC_exampleGame();
    game.Init(true, true);

    return 0;
}