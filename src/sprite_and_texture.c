#include "TGJGE.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

TG_texture* TG_new_texture(
	const char *path, 
	_Bool linear_interpolation_toggle)
{
	TG_texture *new_texture=malloc(sizeof(TG_texture));

	int size_x, size_y, n;
	//4 forces that the output is RGBA
	unsigned char *img_data=stbi_load(path, &size_x, &size_y, &n, 3);
	if(img_data==NULL)
	{
		printf("ERROR: image at %s couldn't be read\n", path);
		return NULL;
	}
	else
	{
		printf("image successfully loaded from %s\n", path);
	}

	GLfloat *tex_data=malloc(size_x*size_y*4*sizeof(GLfloat));
	//converting raw image data to something more OpenGL friendly
	if(n==3) //RGB
	{
		GLfloat *tmp_ptr=tex_data;
		for(int iy=0; iy<size_y; iy++)
		{
			for(int ix=0; ix<size_x; ix++)
			{
				unsigned int n1,n2;
				n1=(iy*size_x+ix)*4;
				n2=(iy*size_x+ix)*3;
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
				//A
				tex_data[n1]=1.0;
			}
		}
	}
	else if(n==4) //RGBA
	{
		GLfloat *tmp_ptr=tex_data;
		for(int iy=0; iy<size_y; iy++)
		{
			for(int ix=0; ix<size_x; ix++)
			{
				unsigned int n=(iy*size_x+ix)*4;
				//R
				tex_data[n]=(float)img_data[n]/255;
				n++;
				//G
				tex_data[n]=(float)img_data[n]/255;
				n++;
				//B
				tex_data[n]=(float)img_data[n]/255;
				n++;
				//A
				tex_data[n]=(float)img_data[n]/255;
			}
		}
	}
	else
	{
		printf("ERROR: the image at %s has no RGB or RGBA values\n", path);
		return NULL;
	}

	GLfloat test_tex[]=
	{
		0.1,0.7,0.1,1.0, 0.4,0.1,0.2,1.0,
		0.4,0.1,0.2,1.0, 0.1,0.7,0.1,1.0,		
	};

	glGenTextures(1, &new_texture->to);
	if(new_texture->to==0)
	{
		printf("texture couldn't be created by OpenGL\n");
	}
	glBindTexture(GL_TEXTURE_2D, new_texture->to);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
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

	return new_texture;
}

void TG_destroy_texture(TG_texture *texture)
{
	glDeleteTextures(1, &texture->to);
	free(texture);
}

