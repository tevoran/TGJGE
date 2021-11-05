#include <TGJGE.h>

#define RED 0.9, 0.1, 0.1, 1.0
#define BLU 0.1, 0.2, 0.9, 1.0

GLfloat test_tex[]=
{
	RED, RED, RED, RED,
	RED, BLU, BLU, RED,
	RED, BLU, BLU, RED,
	BLU, BLU, BLU, BLU
};

int main()
{
	TG_init("test window", 1366, 768, false, 60);

	TG_show_cursor(false);

	TG_music *music=TG_new_music("assets/game-music.wav");
	TG_music_play(music);

	TG_font *font=TG_new_font("assets/OpenSans-Regular.ttf", 500);
	TG_text *text=TG_new_text(
		font, 
		"TGJGE", 
		1.0, 
		1.0, 
		0.0, 
		0.0,
		0.6,
		0.5,
		0.01);



	TG_texture *crate_tex=TG_new_texture_custom(&test_tex, 4, 4, 1, false);
	//TG_new_texture("assets/crate.bmp", 1, false);
	TG_object *crate[10];
	for(int i=0; i<10; i++)
	{
		crate[i]=TG_new_object(0.1,0.178,(float)i/10,0.322);
		TG_object_use_texture(crate[i], crate_tex);
	}

	//animation test
	TG_texture *fire_tex=TG_new_texture("assets/flame.png", 3, false);
	TG_object *fire_obj=TG_new_object(0.058, 0.1, 0.1, 0.5);
	TG_object *fire_obj2=TG_new_object(0.058, 0.1, 0.85, 0.5);
	TG_object_use_texture(fire_obj, fire_tex);
	TG_object_use_texture(fire_obj2, fire_tex);

	TG_object_start_animation(fire_obj, 1, 3, 500, true);
	TG_object_start_animation(fire_obj2, 1, 3, 500, true);

	float x=0,y=0;
	TG_object *mouse=TG_new_object(0.058, 0.1, x, y);
	TG_object_use_texture(mouse, fire_tex);
	TG_object_start_animation(mouse, 1, 3, 350, true);

	while(!TG_is_key_pressed(SDL_SCANCODE_ESCAPE))
	{
		TG_mouse_position(&x, &y);
		TG_set_position_object(mouse, x, y);
		for(int i=0; i<10; i++)
		{
			TG_render_object(crate[i]);
		}
		TG_render_object(fire_obj);
		TG_render_object(fire_obj2);
		TG_render_object(mouse);
		TG_render_text(text);
		TG_new_frame(0.25,0.0,0);
	}

	TG_destroy_font(font);
	TG_destroy_texture(fire_tex);
	TG_destroy_texture(crate_tex);
	TG_destroy_object(fire_obj);
	TG_destroy_object(fire_obj2);
	TG_quit();
	return 0;
}