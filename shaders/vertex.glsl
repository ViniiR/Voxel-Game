#version 460 core

layout(location=0) in vec3 vertex_position;
layout(location=1) in vec3 vertex_color;
layout(location=2) in vec2 texture_coordenate;

uniform mat4 model_matrix;
uniform mat4 projection;
uniform mat4 view_matrix;

out vec3 fragment_color;
out vec2 fragment_texture;

void main()
{
    fragment_color = vertex_color;
    fragment_texture = texture_coordenate;

    gl_Position = projection * view_matrix * model_matrix * vec4(vertex_position, 1.0f);
};
