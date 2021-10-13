#include "TGJGE.h"

//SDL related
SDL_Window *TG_main_window=NULL;
SDL_GLContext TG_gl_context=NULL; //SDL_GLContext is an alias for *void
const Uint8 *TG_keyboard_state = NULL;
SDL_Event TG_event;

//OpenGL related
GLuint TG_vertex_shader=0; //set 0 as initial value
GLuint TG_fragment_shader=0; //set 0 as initial value
GLuint TG_shader_program=0; //set 0 as initial value

//time related variables
unsigned int TG_desired_frametime=0;
unsigned int TG_last_frametime=0;
unsigned int TG_current_frametime=0;
unsigned int TG_delta_frametime=0;