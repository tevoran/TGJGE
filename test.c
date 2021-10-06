#include <TGJGE.h>


int main()
{
	TG_init("test window", 1920, 1080, true);
	TG_flip(0.0,0.0,0.0);
	TG_render();
	TG_flip(0.1,0.25,0.1);
	SDL_Delay(10000);
	return 0;
}