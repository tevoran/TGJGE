#include <TGJGE.h>


int main()
{
	TG_init("test window", 1920, 1080, false, 60);
	TG_flip(0.0,0.0,0.0);
	TG_object *object=TG_new_object(0.2, 0.1, 0.1, 0.5);
	TG_set_position_object(object, 0.5,0.5);
	TG_render_object(object);

	for(int i=0; i<3600; i++)
	{
		TG_set_position_object(object, 0.4*sin((float)i/50)+0.4, 0.5);
		TG_render_object(object);
		TG_flip(0,0,0);
	}


	TG_destroy_object(object);
	return 0;
}