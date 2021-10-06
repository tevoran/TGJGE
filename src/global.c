#include "TGJGE.h"

SDL_Window *TG_main_window=NULL;
SDL_GLContext TG_gl_context=NULL; //SDL_GLContext is an alias for *void
GLuint TG_vertex_shader=0; //set 0 as initial value
GLuint TG_fragment_shader=0; //set 0 as initial value
GLuint TG_shader_program=0; //set 0 as initial value