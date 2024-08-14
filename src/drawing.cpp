#include <glad.h>
#include "Camera.hpp"
#include "ScreenSize.hpp"
#include <cstdlib>
#include <glm/ext/matrix_clip_space.hpp>
#include <iostream>

void draw(GLuint VAO, GLuint vertices_VBO) {
    glBindVertexArray(VAO);

    GLint bound_VAO = 0;

    /*glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &bound_VAO);*/
    /*if (bound_VAO != VAO) {*/
    /*    std::cout << "No VAO bound" << std::endl;*/
    /*    exit(-1);*/
    /*}*/

    /*GLint bufferBinding;*/
    /*glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &bufferBinding);*/
    /*if (bufferBinding == 0) {*/
    /*    std::cerr << "No VBO is bound to the VAO!" << std::endl;*/
    /*} else {*/
    /*    std::cout << "Number of VBOs attached to the VAO:" << bufferBinding*/
    /*              << std::endl;*/
    /*}*/

    /*glDrawArrays(GL_TRIANGLES, 0, 3);*/
    glDrawArrays(GL_TRIANGLES, 0, 12 * 3);

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

    const GLint uniformModelMatrixLocation =  //
        glGetUniformLocation(                 //
            graphicsPipelineShaderProgram,    //
            "model_matrix"                    //
        );
    if (uniformModelMatrixLocation == -1) {
        std::cerr << "model_matrix location not found" << std::endl;
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
            "view_matrix"                    //
        );
    if (uniformViewMatrixLocation == -1) {
        std::cerr << "view_matrix location not found" << std::endl;
        exit(-1);
    }
    glUniformMatrix4fv(uniformViewMatrixLocation, 1, GL_FALSE, &view[0][0]);

    //

    const GLint uniformProjectionLocation =  //
        glGetUniformLocation(                //
            graphicsPipelineShaderProgram,   //
            "projection"                     //
        );
    if (uniformProjectionLocation == -1) {
        std::cerr << "projection location not found" << std::endl;
        exit(-1);
    }

    // how close and far you can see at: 3rd n 4th params
    const glm::mat4 perspective = glm::perspective(
        glm::radians(45.0f), (float)screen.width / (float)screen.height, 0.1f,
        100.0f);
    glUniformMatrix4fv(uniformProjectionLocation, 1, GL_FALSE,
                       &perspective[0][0]);
}
