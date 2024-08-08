#pragma once

#include <SDL2/SDL_video.h>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/vec3.hpp>

class Camera {
    public:
        Camera();
        const glm::mat4 getViewMatrix() const;

        void mouseLook(int mouseX, int mouseY);
        void moveForward(float speed);
        void moveBackward(float speed);
        void moveRight(float speed);
        void moveLeft(float speed);
        void moveUp(float speed);
        void moveDown(float speed);

        float yaw = -90.0f;
        float pitch = -1.0f;

    private:
        glm::vec3 eye;
        glm::vec3 viewDirection;
        glm::vec3 upVector;

        glm::vec2 previousMousePosition;
};
