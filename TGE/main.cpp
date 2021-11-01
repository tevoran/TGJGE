#include <TGE.hpp>

int main()
{
	tge::editor& editor=tge::editor::get();

	editor.main_loop();

	return 0;
}