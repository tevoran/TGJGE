#include <TGE.hpp>


void tge::editor::main_loop()
{
	bool quit=false;
	while(!quit)
	{
		//rendering overlay elements
		//windows
		for(tge::window& window : windows)
		{
			window.render();
		}

		TG_new_frame(0,0,0);
		//checking if program should end
		if(	TG_is_key_pressed(SDL_SCANCODE_ESCAPE) ||
			TG_is_quit_window())
		{
			quit=true;
		}
	}
}