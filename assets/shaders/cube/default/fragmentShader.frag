#version 460 core

in vec3 fragmentColor;

out vec4 Color;

void main()
{
    Color = vec4(fragmentColor, 1.0f);
}