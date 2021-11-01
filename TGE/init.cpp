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

	//creating elements
	new_project=TG_new_object(
		TGE_ELEMENT_SIZE_X,
		TGE_ELEMENT_SIZE_Y,
		TGE_TOOLBAR_POS_X,
		TGE_TOOLBAR_POS_Y);
	TG_object_use_texture(new_project, style);
	TG_object_start_animation(
		new_project,
		TGE_ELEMENT_NEW,
		TGE_ELEMENT_NEW,
		0,
		false);

	save_project=TG_new_object(
		TGE_ELEMENT_SIZE_X,
		TGE_ELEMENT_SIZE_Y,
		TGE_TOOLBAR_POS_X+TGE_ELEMENT_SIZE_X,
		TGE_TOOLBAR_POS_Y);
	TG_object_use_texture(save_project, style);
	TG_object_start_animation(
		save_project,
		TGE_ELEMENT_SAVE,
		TGE_ELEMENT_SAVE,
		0,
		false);
}

tge::editor::~editor()
{
	TG_destroy_texture(style);
	TG_destroy_object(toolbar);
	TG_destroy_object(new_project);
	TG_destroy_object(save_project);
	std::cout << "quitting TGE\n";
	TG_quit();
}