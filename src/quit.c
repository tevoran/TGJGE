#include "TGJGE.h"

extern SDL_Window *TG_main_window;
extern SDL_GLContext TG_gl_context; //SDL_GLContext is an alias for *void

//desktop resolution
extern int TG_desktop_res_x;
extern int TG_desktop_res_y;

void TG_quit()
{
	//resize window to native desktop resolution to avoid strange behaviour
	SDL_SetWindowSize(TG_main_window, TG_desktop_res_x, TG_desktop_res_y);

		printf("delete OpenGL context...");
	SDL_GL_DeleteContext(TG_gl_context);
		printf("done\n");

		printf("destroy the window...");
	SDL_DestroyWindow(TG_main_window);
		printf("done\n");

		printf("quitting SDL2_ttf...");
	TTF_Quit();
		printf("done\n");

		printf("quitting SDL2...");
	SDL_Quit();
		printf("done\n");
}