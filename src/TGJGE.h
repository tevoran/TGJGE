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


struct TG_texture
{
	GLuint to;
} typedef TG_texture;

struct TG_object
{
	//renderer related stuff
	GLuint vao; //vertex array object
	GLuint vbo; //vertex buffer object
	GLuint ibo; //index buffer object
	GLuint to; //texture object

	//transformations
	float scale_x;
	float scale_y;
	float translation_x;
	float translation_y;

} typedef TG_object;

#include "TGJGE_internal.h"

//function definitons
void TG_init(
	const char *window_title, 
	int res_x, 
	int res_y, 
	_Bool fullscreen_toggle,
	float desired_framerate);

	//swaps the framebuffer and takes in the clear color as a parameter
void TG_flip(float r, float g, float b); 
int TG_delta_time();
float TG_delta_time_f();

//2Dobject functions
TG_object* TG_new_object(
	float size_x,
	float size_y,
	float pos_x,
	float pos_y);
void TG_render_object(const TG_object *object);
void TG_destroy_object(TG_object *object);
void TG_use_texture_object(TG_object *object, TG_texture *texture);
void TG_resize_object(TG_object *object, float size_x, float size_y);
void TG_set_position_object(TG_object *object, float pos_x, float pos_y);

TG_texture* TG_new_texture(_Bool nearest);





#endif

#ifdef __cplusplus
	}
#endif