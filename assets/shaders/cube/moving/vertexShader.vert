#version 460 core

layout (location = 0) in vec3 cubeCoordinates;
layout (location = 1) in vec2 textureCoordinates;

out vec2 TexCoord;

uniform mat4 view;
uniform mat4 model;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(cubeCoordinates, 1.0f);
	TexCoord = vec2(textureCoordinates);
}