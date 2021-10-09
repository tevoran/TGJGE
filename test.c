#include <TGJGE.h>


int main()
{
	TG_init("test window", 1920, 1080, true, 60);
	TG_flip(0.0,0.0,0.0);
	TG_texture *texture=TG_new_texture("assets/Taube.png", false);
	TG_object *object=TG_new_object(0.17, 0.3, 0.1, 0.5);
	TG_use_texture_object(object, texture);
	TG_set_position_object(object, 0.5,0.5);

	TG_texture *crate_tex=TG_new_texture("assets/crate.bmp", false);
	TG_object *crate[10];
	for(int i=0; i<10; i++)
	{
		crate[i]=TG_new_object(0.1,0.178,(float)i/10,0.322);
		TG_use_texture_object(crate[i], crate_tex);
	}

	TG_render_object(object);

	for(int i=0; i<1000; i++)
	{
		TG_set_position_object(object, 0.4*sin((float)i/50)+0.4, 0.5);
		TG_render_object(object);
		for(int i=0; i<10; i++)
		{
			TG_render_object(crate[i]);
		}
		TG_flip(0.1,0.0,0);
	}

	TG_destroy_texture(texture);
	TG_destroy_object(object);
	return 0;
}