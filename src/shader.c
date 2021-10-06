#include "TGJGE.h"

extern GLuint TG_vertex_shader; //set 0 as initial value
extern GLuint TG_fragment_shader; //set 0 as initial value
extern GLuint TG_shader_program; //set 0 as initial value

void TG_load_shader(const int shader_type, const char *shader_location)
{
	GLenum error;
	FILE *shader_file=NULL;
	char *shader_buffer=NULL;
	unsigned int shader_size;

	//showing starting message
	if(shader_type==TG_VERTEX)
	{
		printf("loading vertex shader...");
	}
	else if(shader_type==TG_FRAGMENT)
	{
		printf("loading fragment shader...");
	}
	else
	{
		printf("ERROR: can't load shader because it's an unknown type\n");
		return;
	}

	//loading actual shader from file
	shader_file=fopen(shader_location, "r");
	if(shader_file==NULL)
	{
		printf("\nERROR while loading the file at %s", shader_location);
		return;
	}
	else
	{
		printf("done\n");
	}

	//determining the size of the shader file
	fseek(shader_file, 0, SEEK_END);
	shader_size=ftell(shader_file);
	fseek(shader_file, 0, SEEK_SET);

	//getting source ready in memory
	shader_buffer=malloc(shader_size+1);
	shader_buffer[shader_size]=0; //add end of string for the shader compiler
	fread(shader_buffer, shader_size, 1, shader_file);

	//creating the shader for OpenGL
	if(shader_type==TG_VERTEX)
	{
		TG_vertex_shader=glCreateShader(GL_VERTEX_SHADER);
		if(TG_vertex_shader==0)
		{
			printf("ERROR: vertex shader couldn't be created by OpenGL\n");
			return;
		}
		const GLchar *vertex_shader_src=shader_buffer;
		glShaderSource(TG_vertex_shader,1, &vertex_shader_src, NULL);
		glCompileShader(TG_vertex_shader);
		glGetShaderiv(TG_vertex_shader, GL_COMPILE_STATUS, &error);
		if(error!=GL_TRUE)
		{
			printf("ERROR: vertex shader couldn't be compiled\n");
			GLint log_length;
			glGetShaderiv(TG_vertex_shader, GL_INFO_LOG_LENGTH, &log_length);

			char *error_msg=malloc(log_length);
			glGetShaderInfoLog(TG_vertex_shader,log_length, NULL, error_msg);
			printf("OPENGL ERROR LOG:\n %s\n", error_msg);
			free(error_msg);
		}
	}
	else if(shader_type==TG_FRAGMENT)
	{
		TG_fragment_shader=glCreateShader(GL_FRAGMENT_SHADER);
		if(TG_fragment_shader==0)
		{
			printf("ERROR: fragment shader couldn't be created by OpenGL\n");
			return;
		}
		const GLchar *fragment_shader_src=shader_buffer;
		glShaderSource(TG_fragment_shader,1, &fragment_shader_src, NULL);
		glCompileShader(TG_fragment_shader);
		glGetShaderiv(TG_fragment_shader, GL_COMPILE_STATUS, &error);
		if(error!=GL_TRUE)
		{
			printf("ERROR: fragment shader couldn't be compiled\n");
			GLint log_length;
			glGetShaderiv(TG_fragment_shader, GL_INFO_LOG_LENGTH, &log_length);

			char *error_msg=malloc(log_length);
			glGetShaderInfoLog(TG_fragment_shader,log_length, NULL, error_msg);
			printf("OPENGL ERROR LOG:\n %s\n", error_msg);
			free(error_msg);
		}

	}

	//if fragment and vertex shader a both compiled then create a complete
	//shader program
	if(TG_vertex_shader!=0 && TG_fragment_shader!=0)
	{
		if(TG_shader_program==0)
		{
			TG_shader_program=glCreateProgram();
			if(TG_shader_program==0)
			{
				printf("ERROR: OpenGL couldn't create a new shader program\n");
				return;
			}
		}
		glAttachShader(TG_shader_program, TG_vertex_shader);
		glAttachShader(TG_shader_program, TG_fragment_shader);
		glLinkProgram(TG_shader_program);
		glUseProgram(TG_shader_program);
		printf("use new shader program\n");
	}
	fclose(shader_file);
	free(shader_buffer);
}