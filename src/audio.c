#include <TGJGE.h>

//music
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

void TG_music_play_fade_in(TG_music *music, int ms)
{
	if(music==NULL)
	{
		printf("ERROR: no music loaded\n");
		return;
	}
	if(Mix_FadeInMusic(music->music, -1, ms)==-1)
	{
		printf("ERROR MESSAGE:\n%s\n", Mix_GetError());
	}
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

void TG_music_pause()
{
	Mix_PauseMusic();	
}

void TG_music_resume()
{
	Mix_ResumeMusic();
}

void TG_destroy_music(TG_music *music)
{
	Mix_FreeMusic(music->music);
	free(music);
}


//sfx
TG_sfx* TG_new_sfx(const char *path)
{
	TG_sfx *sfx=malloc(sizeof(TG_sfx));
	sfx->chunk=Mix_LoadWAV(path);
	if(sfx->chunk==NULL)
	{
		printf("ERROR: sound effect couldn't be loaded from %s\n", path);
		printf("ERROR MESSAGE:\n%s\n", Mix_GetError());
	}
	else
	{
		printf("sound effect successfully loaded from %s\n", path);
	}
	return sfx;
}

void TG_sfx_play(TG_sfx *sfx)
{
	if(sfx==NULL)
	{
		printf("ERROR: no sound effect loaded\n");
		return;
	}
	if(Mix_PlayChannel(-1, sfx->chunk, 0)==-1)
	{
		printf("ERROR: sound effect couldn't be played\n");
		printf("ERROR MESSAGE:\n%s\n", Mix_GetError());
	}
	return;
}

void TG_destroy_sfx(TG_sfx *sfx)
{
	Mix_FreeChunk(sfx->chunk);
	free(sfx);
}

//pauses all sfx channels
void TG_sfx_pause()
{
	Mix_Pause(-1);
}

//resums all sfx channels
void TG_sfx_resume()
{
	Mix_Resume(-1);
}