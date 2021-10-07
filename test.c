#include <TGJGE.h>


int main()
{
	TG_init("test window", 1366, 768, false);
	TG_flip(0.0,0.0,0.0);
	TG_object *object=TG_new_object(0.2, 0.1, 0.1, 0.5);
	TG_set_position_object(object, 0.5,0.5);
	TG_render_object(object);
	TG_destroy_object(object);
	TG_flip(0.1,0.25,0.1);
	SDL_Delay(10000);
	return 0;
}