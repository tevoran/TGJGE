#include <TGE.hpp>

tge::editor::editor()
{
	std::cout << "starting TGE\n";
	TG_init("TGE", 1366, 768, false, 30);

	//loading editor relevant data
	style=TG_new_texture("TGE/assets/style.png", TGE_STYLE_ELEMENTS, false);

	//creating windows
	std::list<tge::window>::iterator it;
	//toolbar window
	windows.emplace_back(style,
		TGE_TOOLBAR_SIZE_X, 
		TGE_TOOLBAR_SIZE_Y,
		TGE_TOOLBAR_POS_X,
		TGE_TOOLBAR_POS_Y,
		std::string(TGE_TOOLBAR_NAME));
	it=windows.begin();
	it->add_element(TGE_ELEMENT_NEW);
	it->add_element(TGE_ELEMENT_SAVE);
}

tge::editor::~editor()
{
	TG_destroy_texture(style);
	TG_destroy_object(new_project);
	TG_destroy_object(save_project);
	std::cout << "quitting TGE\n";
	TG_quit();
}