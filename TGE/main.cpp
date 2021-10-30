#include <TGJGE.h>
#include <unistd.h>

int main()
{
	TG_init("TGE", 1920, 1080, true, 60);
	TG_new_frame(0,0,0);
	sleep(6);
	TG_quit();
	return 0;
}