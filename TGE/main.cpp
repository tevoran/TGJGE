#include <TGE.hpp>

int main()
{
	TG_init("TGE", 1366, 768, false, 30);

	//main loop
	bool quit=false;
	while(!quit)
	{
		TG_new_frame(0,0,0);
		if(	TG_is_key_pressed(SDL_SCANCODE_ESCAPE) ||
			TG_quit_window())
		{
			quit=true;
		}
	}


	TG_quit();
	return 0;
}