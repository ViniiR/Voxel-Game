#include <glad.h>
#include "Camera.hpp"
#include "ScreenSize.hpp"
#include "cube.hpp"
#include <cstdlib>
#include <glm/ext/matrix_clip_space.hpp>
#include <textures.hpp>

void draw(GLuint VAO, GLuint vertices_VBO) {

    /*static const std::vector<std::vector<GLuint>> cube_faces_indices = {*/
    /*    std::vector<GLuint>{0, 1, 2, 2, 3, 0},*/
    /*    std::vector<GLuint>{4, 5, 6, 6, 7, 4},*/
    /*    std::vector<GLuint>{0, 3, 7, 7, 4, 0},*/
    /*    std::vector<GLuint>{1, 5, 6, 6, 2, 1},*/
    /*    std::vector<GLuint>{3, 2, 6, 6, 7, 3},*/
    /*    std::vector<GLuint>{0, 1, 5, 5, 4, 0},*/
    /*};*/
    glBindTexture(
        GL_TEXTURE_2D,
        load_texture("../textures/blocks/grass_block/grass_side.bmp"));
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    // unbinds current VAO
    glBindVertexArray(0);
}

void pre_draw(Camera *camera, const ScreenSize &screen,
              GLuint graphicsPipelineShaderProgram) {
    /*glDisable(GL_DEPTH_TEST);*/
    // learn about cull face
    glDisable(GL_CULL_FACE);

    glViewport(0, 0, screen.width, screen.height);
    glClearColor(1.f, 1.f, 1.f, 1.f);

    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    glUseProgram(graphicsPipelineShaderProgram);

    //

    camera->create_camera(graphicsPipelineShaderProgram, screen);
}
