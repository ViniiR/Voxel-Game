#include <glm/ext/vector_float2.hpp>
#include <glm/geometric.hpp>
#include <iostream>
#include "ScreenSize.hpp"
#include "glad.h"
#define GLM_ENABLE_EXPERIMENTAL

#include "./hpp/Camera.hpp"
#include <glm/detail/qualifier.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtx/rotate_vector.hpp>

Camera::Camera() {
    eye = glm::vec3(0.f, 0.f, 0.f);
    view_direction = glm::vec3(0.f, 0.f, -1.f);
    up_vector = glm::vec3(0.f, 1.f, 0.f);
}

glm::mat4 Camera::get_view_matrix() const {
    return glm::lookAt(eye, eye + view_direction, up_vector);
}

void Camera::create_camera(GLuint shader_program, ScreenSize screen) {
    const GLint uniformModelMatrixLocation =  //
        glGetUniformLocation(                 //
            shader_program,                   //
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

    glm::mat4 view = this->get_view_matrix();
    const GLint uniformViewMatrixLocation =  //
        glGetUniformLocation(                //
            shader_program,                  //
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
            shader_program,                  //
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

// by the way thanks to learnopengl.com cause without them this shit wouldnt
// work and yes i had to write some of my own shit here (changing and creating
// values at random till it worked(I AM NOT KIDDING LMAO))
void Camera::mouse_look(int mouse_x, int mouse_y) {
    glm::vec2 currentMousePosition = glm::vec2(mouse_x, mouse_y);

    static bool firstLook = true;

    if (firstLook) {
        previous_mouse_position = currentMousePosition;
        firstLook = false;
    }

    float offsetX = currentMousePosition.x - previous_mouse_position.x;
    float offsetY = currentMousePosition.y - previous_mouse_position.y;

    previous_mouse_position = currentMousePosition;

    float mouseSensitivity = 0.1f;
    offsetX *= mouseSensitivity;
    offsetY *= mouseSensitivity;

    yaw += offsetX;
    pitch += offsetY;

    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

    view_direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    view_direction.y = -sin(glm::radians(pitch));
    view_direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
}
void Camera::move_forward(float speed) {
    glm::vec3 forwardDirection =
        glm::normalize(glm::vec3(view_direction.x, 0.0f, view_direction.z));
    eye += forwardDirection * speed;  //
    /*eye += view_direction * speed;  //*/
}
void Camera::move_backward(float speed) {
    glm::vec3 forwardDirection =
        glm::normalize(glm::vec3(view_direction.x, 0.0f, view_direction.z));
    eye -= forwardDirection * speed;  //
    /*eye -= view_direction * speed;  //*/
}
// moving Left or right when exactly on top or bottom of the initial cube and
// looking at it, causes you to move extremely slow
// FIXME:
void Camera::move_right(float speed) {
    glm::vec3 strafeDirection = glm::cross(view_direction, up_vector);

    if (glm::length(strafeDirection) < 0.001f) {
        strafeDirection =
            glm::cross(view_direction, glm::vec3(0.0f, 1.0f, 0.0f));
    }

    eye += speed * glm::normalize(strafeDirection);
    /*glm::vec3 strafeDirection = glm::cross(view_direction, up_vector);*/
    /*eye += speed * strafeDirection;*/
}
void Camera::move_left(float speed) {
    glm::vec3 strafeDirection = glm::cross(view_direction, up_vector);

    if (glm::length(strafeDirection) < 0.001f) {
        strafeDirection =
            glm::cross(view_direction, glm::vec3(0.0f, 1.0f, 0.0f));
    }

    eye -= speed * glm::normalize(strafeDirection);
    /*glm::vec3 strafeDirection = glm::cross(view_direction, up_vector);*/
    /*eye -= speed * strafeDirection;*/
}
void Camera::move_up(float speed) { eye += speed * up_vector; }
void Camera::move_down(float speed) { eye -= speed * up_vector; }
