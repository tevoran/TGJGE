#version 330

layout(location = 0) in vec2 aPos;

void main()
{
	//converting screen coordinates to OpenGL's NDC
	vec2 Pos = aPos * 2;
	Pos = Pos - 1;

	//setting final position
	gl_Position=vec4(Pos, 0.0, 1.0);
}