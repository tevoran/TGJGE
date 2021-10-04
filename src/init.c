#include "TGJGE.h"

extern SDL_Window *TG_main_window;
extern SDL_GLContext TG_gl_context; //SDL_GLContext is an alias for *void

void TG_init(const char* window_title)
{
	printf("starting TGJGE\n");

	printf("starting SDL2...");
		SDL_Init(
			SDL_INIT_TIMER |
			SDL_INIT_VIDEO |
			SDL_INIT_AUDIO |
			SDL_INIT_EVENTS);
	printf("done\n");

	printf("creating window...");
		TG_main_window=SDL_CreateWindow(
			window_title,
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			1366,
			768,
			SDL_WINDOW_OPENGL);

	if(TG_main_window!=NULL)
	{
		printf("done\n");
	}
	else
	{
		printf("ERROR\n");
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
	}

    glClearColor(0.3,0.1,0.1,1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    SDL_GL_SwapWindow(TG_main_window);

		SDL_Delay(3000);

}