//T3V's Game Jam Game Engine main header

#ifdef __cplusplus
	extern "C" {
#endif

#ifndef TGJGE_H
#define TGJGE_H

//necessary standard libraries
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

//necessary additional libraries
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <GL/glew.h>

struct TG_texture
{
	GLuint to;

	//animation system
	_Bool animation_toggle; //false indicates a non animated sprite
	_Bool loop_toggle; //false is a not looping animation
	int num_frames; //total number of frames available
	int default_frame;
	int start_frame; //the start frame of the current animation
	int current_frame; //current frame of the current animation
	int end_frame; //end frame of the current animation
	int current_frame_timer; //timer in ms
	int frame_end_timer; //timer in ms

} typedef TG_texture;

struct TG_object
{
	//renderer related stuff
	GLfloat quad_data[4][4];

	GLuint vao; //vertex array object
	GLuint vbo; //vertex buffer object
	GLuint ibo; //index buffer object
	TG_texture used_texture; //texture object

	//transformations
	float scale_x;
	float scale_y;
	float translation_x;
	float translation_y;
	float rotation[2][2];

} typedef TG_object;

struct TG_font
{
	TTF_Font *font;
} typedef TG_font;

struct TG_text
{
	TG_font *font;
	TG_object *object;
	TG_texture *texture;
} typedef TG_text;

#include "TGJGE_internal.h"

//function definitons
void TG_init(
	const char *window_title, 
	int res_x, 
	int res_y, 
	_Bool fullscreen_toggle,
	float desired_framerate);
void TG_quit();

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
void TG_render_object(TG_object *object);
void TG_destroy_object(TG_object *object);
void TG_object_use_texture(TG_object *object, TG_texture *texture);
void TG_resize_object(TG_object *object, float size_x, float size_y);
void TG_set_position_object(TG_object *object, float pos_x, float pos_y);
void TG_rotate_object(TG_object *object, float radians);
void TG_object_start_animation(
	TG_object *object,
	int start_frame,
	int end_frame, 
	int duration_ms,
	_Bool loop);
void TG_object_stop_animation(TG_object *object);
_Bool TG_is_colliding(TG_object *a, TG_object *b);

//textures
TG_texture* TG_new_texture(
	const char *path,
	int num_frames,
	_Bool linear_interpolation_toggle);
void TG_destroy_texture(TG_texture *texture);

//text
TG_font* TG_new_font(const char *path, unsigned int font_size_pt);
void TG_destroy_font(TG_font *font);
TG_text* TG_new_text(
	TG_font *font, 
	const char *text, 
	float size_x, 
	float size_y, 
	float pos_x, 
	float pos_y,
	float color_r,
	float color_g,
	float color_b);
void TG_render_text(TG_text *text);
void TG_destroy_text(TG_text *text);

//input
_Bool TG_is_key_pressed(unsigned char key);
void TG_mouse_position(float *x, float *y);
_Bool TG_mouse_is_left_pressed();
_Bool TG_mouse_is_right_pressed();



#ifdef __MINGW32__
	#undef main
#endif

#endif

#ifdef __cplusplus
	}
#endif