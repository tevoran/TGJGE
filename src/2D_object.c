#include "TGJGE.h"

#define NUM_INDEX 6 //because we use exclusively quads

extern GLuint TG_shader_program;

TG_object* TG_new_object(float size_x, float size_y, float pos_x, float pos_y)
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

	new_object->scale_x=size_x;
	new_object->scale_y=size_y;
	new_object->translation_x=pos_x;
	new_object->translation_y=pos_y;

	//initializing values
	new_object->to=0;

	return new_object;
}

void TG_render_object(const TG_object *object)
{
	GLint scale=glGetUniformLocation(TG_shader_program, "aScale");
	glUniform2f(scale, object->scale_x, object->scale_y);
	GLint translation=glGetUniformLocation(TG_shader_program, "aTranslation");
	glUniform2f(translation, object->translation_x, object->translation_y);

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

void TG_resize_object(TG_object *object, float size_x, float size_y)
{
	object->scale_x=size_x;
	object->scale_y=size_y;
}

void TG_set_position_object(TG_object *object, float pos_x, float pos_y)
{
	object->translation_x=pos_x;
	object->translation_y=pos_y;
}