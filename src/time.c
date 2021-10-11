#include "TGJGE.h"

extern unsigned int TG_delta_frametime;

//time in ms
int TG_delta_time()
{
	return TG_delta_frametime;
};

//time in ms
float TG_delta_time_f()
{
	return (float)TG_delta_frametime;
};