#version 410 core

layout(location=0) in vec3 vertex_position;
layout(location=1) in vec3 vertex_color;

uniform mat4 model_matrix;
uniform mat4 projection;
uniform mat4 view_matrix;

out vec3 fragment_color;

void main()
{
    fragment_color = vertex_color;

    gl_Position = projection * view_matrix * model_matrix * vec4(vertex_position, 1.0f);
};
