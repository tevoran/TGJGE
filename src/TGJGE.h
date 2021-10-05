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

//swaps the framebuffer and takes in the clear color as a parameter
void TG_flip(float r, float g, float b); 

#endif

#ifdef __cplusplus
	}
#endif