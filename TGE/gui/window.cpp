#include <TGE.hpp>

tge::window::window(
	TG_texture *style, 
	float size_x, 
	float size_y, 
	float pos_x, 
	float pos_y,
	std::string window_name)
{
	m_style=style;
	m_window_name=window_name;
	m_pos_x=pos_x;
	m_pos_y=pos_y;
	m_size_x=size_x;
	m_size_y=size_y;
	m_background=TG_new_object(
		size_x,
		size_y,
		pos_x,
		pos_y);
	TG_object_use_texture(m_background, m_style);
	TG_object_start_animation(
		m_background,
		TGE_WINDOW_BACKGROUND,
		TGE_WINDOW_BACKGROUND,
		0,
		false);
}

void tge::window::add_element(int style_type, std::string description)
{
	tge::element tmp_element;
	tmp_element.type=style_type; //saving the type of the element
	tmp_element.description=description;
	tmp_element.object=TG_new_object(
		TGE_ELEMENT_SIZE_X, 
		TGE_ELEMENT_SIZE_Y,
		m_pos_x+TGE_ELEMENT_SIZE_X*element.size(),
		m_pos_y);
	TG_object_use_texture(tmp_element.object, m_style);
	TG_object_start_animation(
		tmp_element.object,
		style_type,
		style_type,
		0,
		false);
	element.emplace_back(tmp_element);
}

void tge::window::element_interaction(TG_object *mouse)
{
	static bool mouse_down=false;
	//bool mouse_down_this_frame=false;
	for(int i=0; i<element.size(); i++)
	{
		if(	TG_is_colliding(mouse, element[i].object) &&
			TG_mouse_is_left_pressed() && 
			!mouse_down)
		{
			//mouse_down_this_frame=true;
			mouse_down=true;
			switch(element[i].type)
			{
				case TGE_ELEMENT_NEW:
					std::cout << "NEW PROJECT\n";
					break;

				case TGE_ELEMENT_SAVE:
					std::cout << "SAVING PROJECT\n";
					break;

				case TGE_ELEMENT_LOAD:
					std::cout << "LOADING\n";
					break;

				default:
					break;
			}
		}
	}
	//reset mouse trigger if n
	if(mouse_down && !TG_mouse_is_left_pressed())
	{
		mouse_down=false;
	}
}

std::string& tge::window::name()
{
	return m_window_name;
}

void tge::window::show_description(TG_object *mouse)
{
	static int hovering_duration_ms=0;
	static TG_object *current_hovering_object=NULL;
	static tge::info_text_window *description_window=NULL;

	//used for checking if a collision has happened in this frame	
	bool collision=false;
	for(int i=0; i<element.size(); i++)
	{
		if(current_hovering_object)
		{
			if(	current_hovering_object==element[i].object &&
				TG_is_colliding(mouse, element[i].object))
			{
				hovering_duration_ms+=TG_delta_time();
				collision=true;
				if(hovering_duration_ms>TGE_ELEMENT_WHEN_SHOW_DESCRIPTION_MS)
				{
					if(!description_window)
					{
						tge::editor& editor=tge::editor::get();
						description_window= new tge::info_text_window(
							element[i].description,
							editor.get_font(),
							editor.get_style());		
					}
					description_window->render();
				}
			}
		}
		else
		{
			if(TG_is_colliding(mouse, element[i].object))
			{
				current_hovering_object=element[i].object;
				collision=true;
				hovering_duration_ms=0;
				if(!description_window)
				{
					delete description_window;
				}
				description_window=NULL;
			}
		}
	}
	if(collision==false)
	{
		current_hovering_object=NULL;
		hovering_duration_ms=0;
	}
}

void tge::window::render()
{
	TG_render_object(m_background);
	for(int i=0; i<element.size(); i++)
	{
		TG_render_object(element[i].object);
	}
}

tge::window::~window()
{
	for(int i=0; i<element.size(); i++)
	{
		TG_destroy_object(element[i].object);
	}
	TG_destroy_object(m_background);
}