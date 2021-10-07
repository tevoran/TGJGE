#include "TGJGE.h"

#define NUM_INDEX 6 //because we use exclusively quads

TG_object* TG_new_object()
{
	GLfloat quad_data[]=
	{
		0.0,0.0,
		1.0,0.0,
		0.0,1.0,
		1.0,1.0,
	};

	GLuint quad_index[]=
	{
		0,1,2,
		1,2,3,
	};

	TG_object *new_object=malloc(sizeof(TG_object));

	glGenVertexArrays(1, &new_object->vao);
	glGenBuffers(1, &new_object->vbo);
	glGenBuffers(1, &new_object->ibo);

	glBindVertexArray(new_object->vao);
	glBindBuffer(GL_ARRAY_BUFFER, new_object->vbo);
		glBufferData(
			GL_ARRAY_BUFFER, 
			sizeof(quad_data), 
			quad_data, 
			GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, new_object->ibo);
		glBufferData(
			GL_ELEMENT_ARRAY_BUFFER, 
			sizeof(quad_index), 
			quad_index, 
			GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	return new_object;
}

void TG_render_object(const TG_object *object)
{
	glBindVertexArray(object->vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object->ibo);

	glDrawElements(GL_TRIANGLES, NUM_INDEX, GL_UNSIGNED_INT, NULL);
}

void TG_destroy_object(TG_object *object)
{
	glDeleteBuffers(1, &object->vbo);
	glDeleteBuffers(1, &object->ibo);
	glDeleteVertexArrays(1, &object->vao);
	free(object);
}