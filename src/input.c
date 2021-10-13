#include "TGJGE.h"

extern const Uint8 *TG_keyboard_state;
extern int TG_res_x;
extern int TG_res_y;

//currently the SDL Keyboard Scancodes are used
_Bool TG_is_key_pressed(unsigned char key)
{
	return TG_keyboard_state[key];
}

void TG_mouse_position(float *x, float *y)
{
	int tmp_x,tmp_y;

	SDL_GetMouseState(&tmp_x, &tmp_y);

	*x=(float)tmp_x/(float)TG_res_x;
	*y=1.0 - ((float)tmp_y/(float)TG_res_y);
}
