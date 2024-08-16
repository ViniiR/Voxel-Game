#version 460 core

in vec3 fragment_color;
in vec2 fragment_texture;

uniform sampler2D texture_sampler;

out vec4 color;

void main()
{
    //color = vec4(fragment_color, 1.0f);
    color = texture(texture_sampler, fragment_texture) /* * vec4(fragment_color, 1.0f)*/;
};
