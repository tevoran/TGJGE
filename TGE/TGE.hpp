#pragma once

#include "design.hpp"
#include <TGJGE.h>
#include <iostream>
#include <list>
#include <iterator>
#include <string>
#include <vector>

namespace tge
{
	class info_text_window
	{
	private:
		TG_object *background;
		TG_text *text_object;

	public:
		info_text_window(
			std::string text, 
			TG_font *font, 
			TG_texture *style);
		void render();
		~info_text_window();
	};

	struct element
	{
		TG_object *object;
		int style_type;
		std::string description;
	};

	class window
	{
	private:
		std::string m_window_name;
		TG_texture *m_style=NULL;
		TG_object *m_background=NULL;
		float m_pos_x;
		float m_pos_y;
		float m_size_x;
		float m_size_y;

		//elements
		std::vector<tge::element> element;
	public:
		window(
			TG_texture *style, 
			float size_x, 
			float size_y, 
			float pos_x, 
			float pos_y,
			std::string window_name);
		void show_description(TG_object *mouse);
		void render();
		std::string& name();
		void add_element(int style_type, std::string description);
		~window();
	};

	//general editor singleton class
	class editor
	{
	private:
		//data
		TG_texture *style=NULL; //general style of the editor
		TG_font *font=NULL;

		//windows
		std::list<tge::window> windows;

		//elements
		TG_object *new_project=NULL;
		TG_object *save_project=NULL;

		//mouse (collision box)
		float m_mouse_x;
		float m_mouse_y;
		TG_object *m_mouse;

		//functions
		editor();
		~editor();
	public:
		//functions
		void main_loop();
		TG_font* get_font(){return font;};
		TG_texture* get_style(){return style;};

		//singleton related stuff	
		static editor& get(){static editor instance; return instance;};
		editor (const editor&) = delete;
	};

}
