#pragma once

#include "design.hpp"
#include <TGJGE.h>
#include <iostream>

namespace tge
{
	//general editor singleton class
	class editor
	{
	private:
		//data
		TG_texture *style=NULL;

		//windows
		TG_object *toolbar=NULL;

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
