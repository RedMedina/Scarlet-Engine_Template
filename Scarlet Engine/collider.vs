#version 330 core

layout (location = 0) in vec3 position;

// @uniform_name mvp
// @uniform_type mat4
uniform mat4 mvp;

void main()
{
	gl_Position =  mvp * vec4(position, 1.0f);
}