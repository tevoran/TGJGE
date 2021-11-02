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

std::string& tge::window::name()
{
	return m_window_name;
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