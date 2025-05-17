#pragma once

// AVOID USING THIS FILE AS MUCH AS POSSIBLE
// ONLY USE IN INSTANCES WHERE OTHER OPTIONS ARE TOO CUMBERSOME
//
// PROVIDE RATIONALE FOR ALL VARIABLES DEFINED HERE

// Nuklear context is here as it needs to be accessed from IC_game, IC_inputSystem and IC_uiManager
// as such it was best to define it here.
#include "raylib-nuklear.h"
inline nk_context* nkCtx;