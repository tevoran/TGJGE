//T3V's Game Jam Game Engine main header

#ifdef __cplusplus
	extern "C" {
#endif

#ifndef TGJGE_H
#define TGJGE_H

//necessary standard libraries
#include <stdio.h>

//necessary additional libraries
#include <SDL2/SDL.h>
#include <GL/gl.h>


//function definitons
void TG_init(const char* window_title);

#endif

#ifdef __cplusplus
	}
#endif