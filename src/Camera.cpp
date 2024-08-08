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
    viewDirection = glm::vec3(0.f, 0.f, -1.f);
    upVector = glm::vec3(0.f, 1.f, 0.f);
}

const glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(eye, eye + viewDirection, upVector);
}

// by the way thanks to learnopengl.com cause without them this shit wouldnt
// work and yes i had to write some of my own shit here (changing and creating
// values at random till it worked(I AM NOT KIDDING LMAO))
// make mousePos doubles instead of ints
void Camera::mouseLook(int mouseX, int mouseY) {
    glm::vec2 currentMousePosition = glm::vec2(mouseX, mouseY);

    static bool firstLook = true;

    if (firstLook) {
        previousMousePosition = currentMousePosition;
        firstLook = false;
    }

    float offsetX = currentMousePosition.x - previousMousePosition.x;
    float offsetY = currentMousePosition.y - previousMousePosition.y;

    previousMousePosition = currentMousePosition;

    float mouseSensitivity = 0.1f;
    offsetX *= mouseSensitivity;
    offsetY *= mouseSensitivity;

    yaw += offsetX;
    pitch += offsetY;

    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

    viewDirection.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    viewDirection.y = -sin(glm::radians(pitch));
    viewDirection.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    /*eye = glm::normalize(viewDirection);*/

    /**/
    /*glm::vec2 mouseDelta = currentMousePosition - previousMousePosition;*/
    /**/
    /*viewDirection =*/
    /*    glm::rotate(viewDirection * .5f, glm::radians((float)mouseX),
     * upVector);*/
}
void Camera::moveForward(float speed) {
    eye += viewDirection * speed;  //
}
void Camera::moveBackward(float speed) {
    eye -= viewDirection * speed;  //
}
void Camera::moveRight(float speed) {
    glm::vec3 strafeDirection = glm::cross(viewDirection, upVector);
    eye += speed * strafeDirection;
}
void Camera::moveLeft(float speed) {
    glm::vec3 strafeDirection = glm::cross(viewDirection, upVector);
    eye -= speed * strafeDirection;
}
void Camera::moveUp(float speed) { eye += speed * upVector; }
void Camera::moveDown(float speed) { eye -= speed * upVector; }
