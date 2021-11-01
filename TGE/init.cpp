#include <TGE.hpp>

tge::editor::editor()
{
	std::cout << "starting TGE\n";
	TG_init("TGE", 1366, 768, false, 30);

	//loading editor relevant data
	style=TG_new_texture("TGE/assets/style.png", TGE_STYLE_ELEMENTS, false);

	//creating windows
	toolbar=TG_new_object(
		TGE_TOOLBAR_SIZE_X, 
		TGE_TOOLBAR_SIZE_Y,
		TGE_TOOLBAR_POS_X,
		TGE_TOOLBAR_POS_Y);
	TG_object_use_texture(toolbar, style);
	TG_object_start_animation(
		toolbar,
		TGE_WINDOW_BACKGROUND,
		TGE_WINDOW_BACKGROUND,
		0,
		false);
}

tge::editor::~editor()
{
	std::cout << "quitting TGE\n";
	TG_quit();
}