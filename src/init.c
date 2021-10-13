#include "TGJGE.h"
#include "TGJGE_internal.h"

extern SDL_Window *TG_main_window;
extern SDL_GLContext TG_gl_context; //SDL_GLContext is an alias for *void
extern unsigned int TG_desired_frametime;
extern const Uint8 *TG_keyboard_state;
extern SDL_Event TG_event;

extern int TG_res_x;
extern int TG_res_y;

void TG_init(
	const char *window_title, 
	int res_x, 
	int res_y, 
	_Bool fullscreen_toggle,
	float desired_framerate)
{
	printf("starting TGJGE\n");
	TG_res_x=res_x;
	TG_res_y=res_y;

	printf("starting SDL2...");
		SDL_Init(
			SDL_INIT_TIMER |
			SDL_INIT_VIDEO |
			SDL_INIT_AUDIO |
			SDL_INIT_EVENTS);
	printf("done\n");

	printf("creating window...");
		if(fullscreen_toggle==true)
		{
			TG_main_window=SDL_CreateWindow(
				window_title,
				SDL_WINDOWPOS_CENTERED,
				SDL_WINDOWPOS_CENTERED,
				res_x,
				res_y,
				SDL_WINDOW_OPENGL |
				SDL_WINDOW_FULLSCREEN);			
		}
		else
		{
			TG_main_window=SDL_CreateWindow(
				window_title,
				SDL_WINDOWPOS_CENTERED,
				SDL_WINDOWPOS_CENTERED,
				res_x,
				res_y,
				SDL_WINDOW_OPENGL);	
		}


	if(TG_main_window!=NULL)
	{
		printf("done\n");
	}
	else
	{
		printf("ERROR\n");
		return;
	}

	printf("checking if OpenGL version is at least 3.3...");
		if(SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3)!=0)
		{
			printf("ERROR\n");
			return;
		}
		if(SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3)!=0)
		{
			printf("ERROR\n");
			return;
		}
		else
		{
			printf("done\n");
		}

	printf("creating OpenGL context...");
		TG_gl_context=SDL_GL_CreateContext(TG_main_window);

	if(TG_gl_context!=NULL)
	{
		printf("done\n");
	}
	else
	{
		printf("ERROR\n");
		return;
	}

	//using glew to avoid compatibility issues with OpenGL
	if(glewInit()!=GLEW_OK)
	{
		printf("ERROR: GLEW couldn't be initialized\n");
		return;
	}

	//preparing shaders
	TG_load_shader(TG_VERTEX, "shaders/vertex.glsl");
	TG_load_shader(TG_FRAGMENT, "shaders/fragment.glsl");

	//setting certain OpenGL values
	glClearDepth(1.0f);
	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND); //give us transparency!
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//setting engine related stuff
	TG_desired_frametime=1000/desired_framerate;
	printf("trying to keep a frame time of %u ms\n", TG_desired_frametime);

	//setting an initial keyboard state
	while(SDL_PollEvent(&TG_event))
	{
	};
	TG_keyboard_state=SDL_GetKeyboardState(NULL);
}