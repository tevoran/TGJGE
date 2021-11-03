#include <TGE.hpp>

tge::editor::editor()
{
	std::cout << "starting TGE\n";
	TG_init("TGE", 1366, 768, false, 30);

	//loading editor relevant data
	style=TG_new_texture("TGE/assets/style.png", TGE_STYLE_ELEMENTS, false);
	font=TG_new_font("TGE/assets/OpenSans-Regular.ttf", 45);

	//creating mouse (collision box) for interactions with windows and elements
	m_mouse=TG_new_object(0.01,0.01, 0.01, 0.01);

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
	it->add_element(TGE_ELEMENT_NEW, std::string(TGE_ELEMENT_NEW_DESCRIPTION));
	it->add_element(TGE_ELEMENT_LOAD, std::string(TGE_ELEMENT_LOAD_DESCRIPTION));
	it->add_element(TGE_ELEMENT_SAVE, std::string(TGE_ELEMENT_SAVE_DESCRIPTION));
}

tge::editor::~editor()
{
	TG_destroy_object(m_mouse);
	TG_destroy_texture(style);
	std::cout << "quitting TGE\n";
	TG_quit();
}