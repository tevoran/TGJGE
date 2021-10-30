#include <TGJGE.h>

Mix_Music *music=NULL;

void test_audio()
{
	music=Mix_LoadMUS("assets/rain.mp3");
	if(music==NULL)
	{
		printf("ERROR: music couldn't be loaded\n");
		printf("ERROR MESSAGE:\n%s\n", Mix_GetError());
	}
	else
	{
		printf("music successfully loaded\n");
	}
	if(Mix_PlayMusic(music, -1)!=0)
	{
		printf("ERROR MESSAGE:\n%s\n", Mix_GetError());
	}
	else
	{
		printf("MUSIC should play\n");
	}
}