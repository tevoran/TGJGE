#include "TGJGE.h"

extern const Uint8 *TG_keyboard_state;

//currently the SDL Keyboard Scancodes are used
_Bool TG_is_key_pressed(unsigned char key)
{
	return TG_keyboard_state[key];
}