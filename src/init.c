#include "TGJGE.h"

extern SDL_Window *TG_main_window;

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
			0);

	if(TG_main_window!=NULL)
	{
		printf("done\n");
	}
	else
	{
		printf("ERROR\n");
	}

		SDL_Delay(3000);

}