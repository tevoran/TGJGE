#include <TGJGE.h>

int main()
{
	TG_init("TGE", 800, 800, false, 60);
	SDL_Delay(6000);
	TG_quit();
	return 0;
}