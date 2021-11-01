#pragma once

#include "design.hpp"
#include <TGJGE.h>
#include <iostream>

#define TGE_STYLE_ELEMENTS 1 //the number of elements in the style image

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
