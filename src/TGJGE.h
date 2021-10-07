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
#include <GL/glew.h>

struct TG_object
{
	GLuint vao;
	GLuint vbo;
	GLuint ibo;
} typedef TG_object;

#include "TGJGE_internal.h"

//function definitons
void TG_init(const char *window_title, int res_x, int res_y, _Bool fullscreen_toggle);
//swaps the framebuffer and takes in the clear color as a parameter
void TG_flip(float r, float g, float b); 

TG_object* TG_new_object();
void TG_render_object(const TG_object *object);
void TG_destroy_object(TG_object *object);




#endif

#ifdef __cplusplus
	}
#endif