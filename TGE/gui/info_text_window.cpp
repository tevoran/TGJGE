#include <TGE.hpp>

//used for displaying the little information window when hovering above
//an icon with the mouse
tge::info_text_window::info_text_window(
	std::string text, 
	TG_font *font, 
	TG_texture *style)
{
	float size_x=TGE_ELEMENT_DESCRIPTION_LETTER_SIZE_X*text.length();
	float size_y=TGE_ELEMENT_DESCRIPTION_SIZE_Y;
	float pos_x;
	float pos_y;
	TG_mouse_position(&pos_x, &pos_y);
	background=TG_new_object(size_x, size_y, pos_x, pos_y-size_y);
	TG_object_use_texture(background, style);
	TG_object_start_animation(
		background,
		TGE_WINDOW_BACKGROUND,
		TGE_WINDOW_BACKGROUND,
		0,
		false);

	//text that gets displayed on top of the background
	text_object=TG_new_text(
		font,
		text.c_str(),
		size_x,
		size_y,
		pos_x,
		pos_y-size_y,
		TGE_TEXT_COLOR);
}

void tge::info_text_window::render()
{
	TG_render_object(background);
	TG_render_text(text_object);
}

tge::info_text_window::~info_text_window()
{
	TG_destroy_object(background);
	TG_destroy_text(text_object);
}