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

		//windows
		std::list<tge::window> windows;

		//elements
		TG_object *new_project=NULL;
		TG_object *save_project=NULL;

		//functions
		editor();
		~editor();
	public:
		//functions
		void main_loop();

		//singleton related stuff	
		static editor& get(){static editor instance; return instance;};
		editor (const editor&) = delete;
	};

}
