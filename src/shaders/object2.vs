/*
 * @file
 * @author Vsevolod (Seva) Ivanov
*/

#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec3 offset;
//layout (location = 4) in float alpha;


out vec3 pos;
out vec3 norm;
out vec3 col;
out float alp;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(position + offset, 1.0f);
    gl_PointSize = 5.0;
    pos = position;
	norm = normal;
	col = color;
	//alp = alpha;
}