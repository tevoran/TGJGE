#include <TGJGE.h>

Mix_Music *music=NULL;

TG_music* TG_new_music(const char *path)
{
	TG_music *music=malloc(sizeof(TG_music));
	music->music=Mix_LoadMUS(path);
	if(music->music==NULL)
	{
		printf("ERROR: music couldn't be loaded from %s\n", path);
		printf("ERROR MESSAGE:\n%s\n", Mix_GetError());
	}
	else
	{
		printf("music successfully loaded from %s\n", path);
	}
	return music;
}

void TG_music_play(TG_music *music)
{
	if(music==NULL)
	{
		printf("ERROR: no music loaded\n");
		return;
	}
	if(Mix_PlayMusic(music->music, -1)!=0)
	{
		printf("ERROR MESSAGE:\n%s\n", Mix_GetError());
	}
}

void TG_destroy_music(TG_music *music)
{
	Mix_FreeMusic(music->music);
	free(music);
}
