#version 410 core

in vec3 vertexColors;

out vec4 color;

void main()
{
    color = vec4(vertexColors.r, vertexColors.g, vertexColors.b, 1.0f);
};
