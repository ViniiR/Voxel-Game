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
        const glm::mat4 get_view_matrix() const;

        void mouse_look(int mouse_x, int mouse_y);
        void move_forward(float speed);
        void move_backward(float speed);
        void move_right(float speed);
        void move_left(float speed);
        void move_up(float speed);
        void move_down(float speed);

        float yaw = -90.0f;
        float pitch = -1.0f;

    private:
        glm::vec3 eye;
        glm::vec3 view_direction;
        glm::vec3 up_vector;
        glm::vec2 previous_mouse_position;
};
