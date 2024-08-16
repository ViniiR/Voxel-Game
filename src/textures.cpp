#include <iostream>
#include <string>
#include "glad.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

GLuint load_texture(const std::string texture_path) {
    int height = 0;
    int width = 0;
    int nr_channels = 0;

    unsigned char *data =
        stbi_load(texture_path.data(), &width, &height, &nr_channels, 0);

    GLuint texture = 0;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_LINEAR);

    if (!data) {
        std::cout << "unable to load texture:" << texture_path << std::endl;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_set_flip_vertically_on_load(true);

    //
    stbi_image_free(data);

    return texture;
}
