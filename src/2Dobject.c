#include "TGJGE.h"


void TG_render()
{

	GLfloat tri[]=
	{
		0.1,0.1,
		0.8,0.2,
		0.3,0.7,
	};

	GLuint vao;
	GLuint vbo;

	glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(tri), tri, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	glDrawArrays(GL_TRIANGLES, 0, 3);
}