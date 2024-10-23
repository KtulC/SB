#pragma once
#include <stdio.h>
#include <Windows.h> 
#include <mmsystem.h> 
#pragma comment(lib, "Winmm.lib")

#include "render.h"
#include "game.h"
#include "filesave.h" 
int next_frame(graphic_element* , render_info* , cur_game_info*, int);
