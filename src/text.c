#include "TGJGE.h"

TG_font* TG_new_font(const char *path, unsigned int font_size_pt)
{
	printf("reading font from %s...", path);
	TTF_Font* font=TTF_OpenFont(path, font_size_pt);
	if(font==NULL)
	{
		printf("ERROR\n");
		printf("font couldn't be read from %s\n", path);
		printf("ERROR message:\n %s\n", TTF_GetError());
	}
	else
	{
		printf("done\n");
	}
	TG_font *font_out=malloc(sizeof(TG_font));
	font_out->font=font;
}

void TG_destroy_font(TG_font *font)
{
	TTF_CloseFont(font->font);
	free(font);
}

TG_text* TG_new_text(
	TG_font *font, 
	const char *text, 
	float size_x, 
	float size_y, 
	float pos_x, 
	float pos_y,
	float color_r,
	float color_g,
	float color_b)
{
	TG_text *text_out = malloc(sizeof(TG_text));

	text_out->object = TG_new_object(
		size_x,
		size_y,
		pos_x,
		pos_y,
		1);

	text_out->texture = malloc(sizeof(TG_texture));

	SDL_Color color=
	{
		(unsigned char)(255.0*color_r),
		(unsigned char)(255.0*color_g),
		(unsigned char)(255.0*color_b),
		255
	};

	SDL_Surface *text_surface=TTF_RenderUTF8_Solid(font->font, text, color);
	if(text_surface==NULL)
	{
		printf("ERROR: text couldn't be rendered into a texture\n");
		printf("SDL2_ttf error message:\n%s\n", TTF_GetError());
	}

	//convert to RGBA format
	const SDL_PixelFormat *format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA32);
	if(format==NULL)
	{
		printf("ERROR: color format couldn't be allocated RGBA\n");
		printf("SDL2 error message:\n%s\n", SDL_GetError());	
	}

	SDL_Surface *text_surface_rgba_u8=
		SDL_ConvertSurface(text_surface, format, 0);
	if(text_surface_rgba_u8==NULL)
	{
		printf("ERROR: text surface couldn't be converted into RGBA\n");
		printf("SDL2 error message:\n%s\n", SDL_GetError());		
	}
	SDL_FreeSurface(text_surface);

	//flipping texture
	unsigned char *flipped_text=malloc(text_surface_rgba_u8->w*text_surface_rgba_u8->h*4);
	unsigned char *rgba_text=text_surface_rgba_u8->pixels;

	unsigned int n1=0;
	for(int iy=text_surface_rgba_u8->h-1; iy>=0; iy--)
	{
		for(int ix=0; ix<text_surface_rgba_u8->w; ix++)
		{
			unsigned int n2=(iy*text_surface_rgba_u8->w+ix)*4;
			//R
			flipped_text[n1]=rgba_text[n2];
			n1++;
			n2++;
			//G
			flipped_text[n1]=rgba_text[n2];
			n1++;
			n2++;
			//B
			flipped_text[n1]=rgba_text[n2];
			n1++;
			n2++;
			//A
			flipped_text[n1]=rgba_text[n2];		
			n1++;
		}
	}

	glGenTextures(1, &text_out->texture->to);
	if(text_out->texture->to==0)
	{
		printf("texture couldn't be created by OpenGL\n");
	}
	glBindTexture(GL_TEXTURE_2D, text_out->texture->to);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	glTexImage2D(
		GL_TEXTURE_2D, 
		0, 
		GL_RGBA, 
		text_surface->w, text_surface->h, 
		0, 
		GL_RGBA,
		GL_UNSIGNED_BYTE, 
		flipped_text);
	
	TG_use_texture_object(text_out->object, text_out->texture);

	SDL_FreeSurface(text_surface_rgba_u8);
	free(flipped_text);

	return text_out;
}

void TG_render_text(TG_text *text)
{
	TG_render_object(text->object);
}

void TG_destroy_text(TG_text *text)
{
	TG_destroy_texture(text->texture);
	TG_destroy_object(text->object);
}