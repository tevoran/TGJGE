#version 330

layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 aTex;

uniform vec2 aScale;
uniform vec2 aTranslation;

out vec2 tex_coords;

void main()
{
	vec2 Pos = aPos;

	//transforming the quad
	Pos = aScale * Pos;
	Pos = aTranslation + Pos;

	//converting screen coordinates to OpenGL's NDC
	Pos = Pos * 2;
	Pos = Pos - 1;

	//setting final position
	gl_Position=vec4(Pos, 0.0, 1.0);

	//sending information to the fragment shader
	tex_coords=aTex;
}