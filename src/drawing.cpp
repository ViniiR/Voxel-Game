#include <glad.h>
#include "Camera.hpp"
#include "ScreenSize.hpp"
#include <glm/ext/matrix_clip_space.hpp>
#include <iostream>

void draw(GLuint VAO) {
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VAO);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void pre_draw(Camera *camera, const ScreenSize &screen,
              GLuint graphicsPipelineShaderProgram) {
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    glViewport(0, 0, screen.width, screen.height);
    glClearColor(1.f, 1.f, 1.f, 1.f);

    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    glUseProgram(graphicsPipelineShaderProgram);

    //

    const GLint uniformModelMatrixLocation =  //
        glGetUniformLocation(                 //
            graphicsPipelineShaderProgram,    //
            "uModelMatrix"                    //
        );
    if (uniformModelMatrixLocation == -1) {
        std::cerr << "model matrix location not found" << std::endl;
        exit(-1);
    }

    // in case a square is not seen: the translation.z is 0 which means it is
    // inside the camera, below the minimal viewable distance of 0.1
    const glm::mat4 translate =
        glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -10.0f));
    glUniformMatrix4fv(uniformModelMatrixLocation, 1, GL_FALSE,
                       &translate[0][0]);

    //

    glm::mat4 view = camera->get_view_matrix();
    const GLint uniformViewMatrixLocation =  //
        glGetUniformLocation(                //
            graphicsPipelineShaderProgram,   //
            "uViewMatrix"                    //
        );
    if (uniformViewMatrixLocation == -1) {
        std::cerr << "uniform viewMatrix location location not found"
                  << std::endl;
        exit(-1);
    }
    glUniformMatrix4fv(uniformViewMatrixLocation, 1, GL_FALSE, &view[0][0]);

    //

    const GLint uniformProjectionLocation =  //
        glGetUniformLocation(                //
            graphicsPipelineShaderProgram,   //
            "uProjection"                    //
        );
    if (uniformProjectionLocation == -1) {
        std::cerr << "uniform uProjection location not found" << std::endl;
        exit(-1);
    }

    // how close and far you can see at: 3rd n 4th params
    const glm::mat4 perspective = glm::perspective(
        glm::radians(45.0f), (float)screen.width / (float)screen.height, 0.1f,
        100.0f);
    glUniformMatrix4fv(uniformProjectionLocation, 1, GL_FALSE,
                       &perspective[0][0]);
}
