#version 460 core

layout (location = 0) in vec3 CubePos;
layout (location = 1) in vec3 CubeColor;

uniform mat4 transformMat;

out vec3 fragmentColor;

void main()
{
    // update the cube coordinates by rotating it using transform matrix
    gl_Position = transformMat * vec4(CubePos * 0.5, 1.0);
    fragmentColor = CubeColor;
}
