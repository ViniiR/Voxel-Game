#version 410 core

layout(location=0) in vec3 position;
layout(location=1) in vec3 vColors;

out vec3 vertexColors;

void main()
{
    vertexColors = vColors;
    gl_Position = vec4(position.x, position.y, position.z, 1.0f);
};
