#include "TGJGE.h"

TG_texture* TG_new_texture(_Bool nearest)
{
	TG_texture *new_texture=malloc(sizeof(TG_texture));

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
		if(nearest==true)
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		}
		else
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 2, 2, 0, GL_RGBA, GL_FLOAT, test_tex);

	return new_texture;
}