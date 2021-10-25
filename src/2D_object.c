#include "TGJGE.h"

#define NUM_INDEX 6 //because we use exclusively quads

extern GLuint TG_shader_program;


//helper function
void TG_set_anim_frame(TG_object *object)
{
	//set new texture coordinates
	object->quad_data[0][2]=
		((GLfloat)object->used_texture.current_frame-1.0) / (GLfloat)object->used_texture.num_frames;

	object->quad_data[1][2]=
		((GLfloat)object->used_texture.current_frame) / (GLfloat)object->used_texture.num_frames;

	object->quad_data[2][2]=
		((GLfloat)object->used_texture.current_frame-1.0) / (GLfloat)object->used_texture.num_frames;

	object->quad_data[3][2]=
		((GLfloat)object->used_texture.current_frame) / (GLfloat)object->used_texture.num_frames;

	glBindVertexArray(object->vao);
	glBindBuffer(GL_ARRAY_BUFFER, object->vbo);
	glBufferData(
		GL_ARRAY_BUFFER, 
		sizeof(object->quad_data), 
		object->quad_data, 
		GL_STATIC_DRAW);	
}


TG_object* TG_new_object(
	float size_x,
	float size_y, 
	float pos_x, 
	float pos_y)
{

	GLuint quad_index[]=
	{
		0,1,2,
		1,2,3,
	};

	TG_object *new_object=malloc(sizeof(TG_object));

	/* array visualization
	{
		0.0,0.0,	0.0,0.0,
		1.0,0.0,	1.0,0.0,
		0.0,1.0,	0.0,1.0,
		1.0,1.0,	1.0,1.0,
	}*/

	new_object->quad_data[0][0]=0.0;
	new_object->quad_data[0][1]=0.0;
	new_object->quad_data[0][2]=0.0;
	new_object->quad_data[0][3]=0.0;

	new_object->quad_data[1][0]=1.0;
	new_object->quad_data[1][1]=0.0;
	new_object->quad_data[1][2]=1.0;
	new_object->quad_data[1][3]=0.0;

	new_object->quad_data[2][0]=0.0;
	new_object->quad_data[2][1]=1.0;
	new_object->quad_data[2][2]=0.0;
	new_object->quad_data[2][3]=1.0;

	new_object->quad_data[3][0]=1.0;
	new_object->quad_data[3][1]=1.0;
	new_object->quad_data[3][2]=1.0;
	new_object->quad_data[3][3]=1.0;

	glGenVertexArrays(1, &new_object->vao);
	glGenBuffers(1, &new_object->vbo);
	glGenBuffers(1, &new_object->ibo);

	glBindVertexArray(new_object->vao);
	glBindBuffer(GL_ARRAY_BUFFER, new_object->vbo);
		glBufferData(
			GL_ARRAY_BUFFER, 
			sizeof(new_object->quad_data), 
			new_object->quad_data, 
			GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, new_object->ibo);
		glBufferData(
			GL_ELEMENT_ARRAY_BUFFER, 
			sizeof(quad_index), 
			quad_index, 
			GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*4, (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(
		1, 
		2, 
		GL_FLOAT, 
		GL_FALSE, 
		sizeof(GLfloat)*4, 
		(void*)(2*sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	new_object->scale_x=size_x;
	new_object->scale_y=size_y;
	new_object->translation_x=pos_x;
	new_object->translation_y=pos_y;
	new_object->rotation[0][0]=1.0;
	new_object->rotation[0][1]=0.0;
	new_object->rotation[1][0]=0.0;
	new_object->rotation[1][1]=1.0;


	return new_object;
}

void TG_render_object(TG_object *object)
{
	GLint scale=glGetUniformLocation(TG_shader_program, "aScale");
	glUniform2f(scale, object->scale_x, object->scale_y);
	GLint translation=glGetUniformLocation(TG_shader_program, "aTranslation");
	glUniform2f(translation, object->translation_x, object->translation_y);
	GLint rotation=glGetUniformLocation(TG_shader_program, "aRot");
	glUniformMatrix2fv(
		rotation, 
		1, 
		GL_FALSE, 
		(const GLfloat*)object->rotation);

	//if animation is set to running then set the current frame if necessary
	if(object->used_texture.animation_toggle)
	{
		object->used_texture.current_frame_timer+=TG_delta_time();
		//set new frame if old one is expired
		if(object->used_texture.current_frame_timer > object->used_texture.frame_end_timer)
		{
			object->used_texture.current_frame_timer=0;
			object->used_texture.current_frame++;
			if(object->used_texture.current_frame > object->used_texture.end_frame)
			{
				object->used_texture.animation_toggle=object->used_texture.loop_toggle;
				object->used_texture.current_frame=object->used_texture.default_frame;
			}

			//set new texture coordinates
			TG_set_anim_frame(object);
		}
	}

	glBindVertexArray(object->vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object->ibo);
	if(glIsTexture(object->used_texture.to))
	{
		glBindTexture(GL_TEXTURE_2D, object->used_texture.to);
	}
	else
	{
		printf("ERROR: an invalid texture detected\n");
	}

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

void TG_rotate_object(TG_object *object, float radians)
{
	object->rotation[0][0]=cos(radians);
	object->rotation[0][1]=-sin(radians);
	object->rotation[1][0]=sin(radians);
	object->rotation[1][1]=cos(radians);
}

void TG_object_use_texture(TG_object *object, TG_texture *texture)
{
	object->used_texture=*texture;
}


//animations
void TG_object_start_animation(
	TG_object *object,
	int start_frame, 
	int end_frame, 
	int duration_ms,
	_Bool loop)
{
	object->used_texture.animation_toggle=true;
	object->used_texture.loop_toggle=loop;
	object->used_texture.current_frame=start_frame;
	object->used_texture.default_frame=start_frame;
	object->used_texture.end_frame=end_frame;
	object->used_texture.current_frame_timer=0;
	object->used_texture.frame_end_timer=duration_ms;
	TG_set_anim_frame(object);
}

void TG_object_stop_animation(TG_object *object)
{
	object->used_texture.current_frame=object->used_texture.default_frame;
	TG_set_anim_frame(object);
	object->used_texture.animation_toggle=false;
}


//collisions
_Bool TG_is_colliding(TG_object *a, TG_object *b)
{
	_Bool collision=false;
	if(
		((a->translation_x + a->scale_x) > b->translation_x) &&
		(a->translation_x < (b->translation_x + b->scale_x)) &&
		((a->translation_y + a->scale_y) > b->translation_y) &&
		(a->translation_y < (b->translation_y + b->scale_y))
	)
	{
		collision=true;
	}
	return collision;
}