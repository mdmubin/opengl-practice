#version 460 core

layout (location = 0) in vec3 aPos;

out vec4 color;

void main()
{
    gl_Position = vec4(aPos, 1.0f);
    if (aPos.x > 0.0f)
    {
        if (aPos.y > 0.0f) {
            color = vec4(0.760, 0.368, 0.388, 1.0);
        }
        else {
            color = vec4(0.325, 0.000, 0.043, 1.0);
        }
    }
    else
    {
        if (aPos.y > 0.0f) {
            color = vec4(0.000, 0.788, 0.898, 1.000);
        }
        else {
            color = vec4(0.952, 0.933, 0.850, 1.000);
        }
    }
}
