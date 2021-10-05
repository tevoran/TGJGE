//T3V's Game Jam Game Engine main header

#ifdef __cplusplus
	extern "C" {
#endif

#ifndef TGJGE_H
#define TGJGE_H

//necessary standard libraries
#include <stdio.h>
#include <stdbool.h>

//necessary additional libraries
#include <SDL2/SDL.h>
#include <GL/gl.h>


//function definitons
void TG_init(const char *window_title, int res_x, int res_y, _Bool fullscreen_toggle);

#endif

#ifdef __cplusplus
	}
#endif