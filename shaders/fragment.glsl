#version 330

in vec2 tex_coords;
uniform sampler2D used_texture;

out vec4 color;

void main() 
{
	vec4 color_tmp = texture(used_texture, tex_coords);
	color=color_tmp;
}