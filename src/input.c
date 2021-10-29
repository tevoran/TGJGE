#include "TGJGE.h"

extern const Uint8 *TG_keyboard_state;
extern int TG_res_x;
extern int TG_res_y;

Uint32 TG_mouse_button_state;

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

_Bool TG_mouse_is_left_pressed()
{
	TG_mouse_button_state=SDL_GetMouseState(NULL, NULL);
	return (SDL_BUTTON(SDL_BUTTON_LEFT) & TG_mouse_button_state);
}

_Bool TG_mouse_is_right_pressed()
{
	TG_mouse_button_state=SDL_GetMouseState(NULL, NULL);
	return (SDL_BUTTON(SDL_BUTTON_RIGHT) & TG_mouse_button_state);
}

void TG_show_cursor(_Bool toggle)
{
	if(toggle)
	{
		SDL_ShowCursor(SDL_ENABLE);
	}
	else
	{
		SDL_ShowCursor(SDL_DISABLE);
	}
}
