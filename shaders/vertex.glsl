#version 330

layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 aTex;

uniform vec2 aScale;
uniform vec2 aTranslation;
uniform mat2 aRot;

out vec2 tex_coords;

void main()
{
	vec2 Pos = aPos;

	//transforming the quad
	Pos = vec2(Pos.x - 0.5, Pos.y - 0.5); //used to rotate the quad around its center
	Pos = aRot * Pos;
	Pos = vec2(Pos.x + 0.5, Pos.y + 0.5); //used to rotate the quad around its center
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