#include <glm/ext/vector_float2.hpp>
#include <glm/geometric.hpp>
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
    eye += view_direction * speed;  //
}
void Camera::move_backward(float speed) {
    eye -= view_direction * speed;  //
}
void Camera::move_right(float speed) {
    glm::vec3 strafeDirection = glm::cross(view_direction, up_vector);
    eye += speed * strafeDirection;
}
void Camera::move_left(float speed) {
    glm::vec3 strafeDirection = glm::cross(view_direction, up_vector);
    eye -= speed * strafeDirection;
}
void Camera::move_up(float speed) { eye += speed * up_vector; }
void Camera::move_down(float speed) { eye -= speed * up_vector; }

