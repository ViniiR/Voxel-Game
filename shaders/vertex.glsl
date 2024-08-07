#version 410 core

layout(location=0) in vec3 position;
layout(location=1) in vec3 vColors;

uniform mat4 uModelMatrix;
uniform mat4 uProjection;
uniform mat4 uViewMatrix;

out vec3 vertexColors;

void main()
{
    vertexColors = vColors;

    vec4 uPos = uProjection * uViewMatrix * uModelMatrix * vec4(position, 1.0f);

    gl_Position = uPos;
    //gl_Position = vec4(position.x, position.y, position.z, 1.0f);
};
