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

void Camera::mouseLook(int mouseX, int mouseY) {
    /*static bool firstLook = true;*/
    /*glm::vec2 currentMousePosition = glm::vec2(mouseX, mouseY);*/
    /*if (firstLook) {*/
    /*    previousMousePosition = currentMousePosition;*/
    /*    firstLook = false;*/
    /*}*/
    /**/
    /*glm::vec2 mouseDelta = previousMousePosition = currentMousePosition;*/
    /**/
    /*viewDirection =*/
    /*    glm::rotate(viewDirection, glm::radians((float)mouseX), upVector);*/
    /**/
    /*previousMousePosition = currentMousePosition;*/
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
void Camera::moveUp(float speed) {
    eye += speed * upVector;
}
void Camera::moveDown(float speed) {
    eye -= speed * upVector;
}
