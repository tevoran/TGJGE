#include "TGJGE.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

TG_texture* TG_new_texture(
	const char *path,
	int num_frames,
	_Bool linear_interpolation_toggle)
{
	TG_texture *new_texture=malloc(sizeof(TG_texture));

	int size_x, size_y, n;
	//4 forces that the output is RGBA
	unsigned char *img_data=stbi_load(path, &size_x, &size_y, &n, STBI_rgb_alpha);
	if(img_data==NULL)
	{
		printf("ERROR: image at %s couldn't be read\n", path);
		return NULL;
	}
	else
	{
		printf("image successfully loaded with %i channels from %s\n", n, path);
	}

	GLfloat *tex_data=malloc(size_x*size_y*4*sizeof(GLfloat));
	//converting raw image data to something more OpenGL friendly
	unsigned int n1=0;
	for(int iy=0; iy<size_y; iy++)
	{
		for(int ix=0; ix<size_x; ix++)
		{
			unsigned int n2=(iy*size_x+ix)*4;
			//R
			tex_data[n1]=(float)img_data[n2]/255;
			n1++;
			n2++;
			//G
			tex_data[n1]=(float)img_data[n2]/255;
			n1++;
			n2++;
			//B
			tex_data[n1]=(float)img_data[n2]/255;
			n1++;
			n2++;
			//A
			tex_data[n1]=((float)img_data[n2]/255);		
			n1++;
		}
	}


	glGenTextures(1, &new_texture->to);
	if(new_texture->to==0)
	{
		printf("texture couldn't be created by OpenGL\n");
	}
	glBindTexture(GL_TEXTURE_2D, new_texture->to);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		if(linear_interpolation_toggle==true)
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
		else
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		}
	glTexImage2D(
		GL_TEXTURE_2D, 
		0, 
		GL_RGBA, 
		size_x, size_y, 
		0, 
		GL_RGBA, 
		GL_FLOAT, 
		tex_data);

	free(tex_data);
	stbi_image_free(img_data);

	//animation default setup
	if(num_frames>1)
	{
		new_texture->animation_toggle=true;		
	}
	else
	{
		new_texture->animation_toggle=false;
	}
	new_texture->num_frames=num_frames;
	new_texture->loop_toggle=false;
	new_texture->default_frame=1;
	new_texture->start_frame=1;
	new_texture->current_frame=1;
	new_texture->end_frame=1; //end frame of the current animation
	new_texture->current_frame_timer=0; //ms
	new_texture->frame_end_timer=0; //ms

	return new_texture;
}

void TG_destroy_texture(TG_texture *texture)
{
	glDeleteTextures(1, &texture->to);
	free(texture);
}

