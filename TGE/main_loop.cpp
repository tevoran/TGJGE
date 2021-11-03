#include <TGE.hpp>


void tge::editor::main_loop()
{
	bool quit=false;
	while(!quit)
	{
		//interactions with windows and elements
		TG_mouse_position(&m_mouse_x, &m_mouse_y);
		TG_set_position_object(m_mouse, m_mouse_x, m_mouse_y);

		for(tge::window& window : windows)
		{
			window.element_interaction(m_mouse);
		}

		//rendering overlay elements
		//windows and their elements
		for(tge::window& window : windows)
		{
			window.render();
			window.show_description(m_mouse); //shows an icon descripton
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