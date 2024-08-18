#include "Block.hpp"
#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cube.hpp>
#include <string>
#include "glad.h"

static const std::string textures_dir = "../textures/";
static const std::string grass_block_dir = textures_dir + "blocks/grass_block/";
static const std::string stone_block_dir = textures_dir + "blocks/stone_block/";

BlockTextures GrassTextures(grass_block_dir + "grass_side.bmp",

                            grass_block_dir + "grass_side.bmp",
                            grass_block_dir + "grass_side.bmp",
                            grass_block_dir + "grass_side.bmp",
                            grass_block_dir + "grass_side.bmp",

                            grass_block_dir + "grass_top.bmp",
                            grass_block_dir + "grass_bottom.bmp");

Block::Block(GLuint VAO, GLuint EBO, BlockTextures textures) {
    this->VAO = VAO;
    this->EBO = EBO;

    this->right_face_texture = textures.right_face_texture;
    this->left_face_texture = textures.left_face_texture;
    this->top_face_texture = textures.top_face_texture;
    this->bottom_face_texture = textures.bottom_face_texture;
    this->back_face_texture = textures.back_face_texture;
    this->front_face_texture = textures.front_face_texture;
    this->multi_face_texture = textures.multi_face_texture;
}

void Block::tmp_draw_lottacubes(GLuint shader_program,
                                unsigned int cube_number = 1) {
    static const GLuint model_matrix_location = glGetUniformLocation(  //
        shader_program,                                                //
        "model_matrix"                                                 //
    );
    for (unsigned int i = 0; i < cube_number; i++) {
        glm::mat4 model = glm::mat4(1.0f);  // Identity matrix

        // Calculate the position of the cube
        glm::vec3 position =
            glm::vec3(i * 1.0f, 0.0f, 0.0f);  // Move cubes along the x-axis

        // Apply translation
        model = glm::translate(model, position);

        // Send the model matrix to your shader
        glUniformMatrix4fv(model_matrix_location, 1, GL_FALSE,
                           glm::value_ptr(model));

        this->draw_block();
    }

    for (unsigned int i = 0; i < cube_number; i++) {
        glm::mat4 model = glm::mat4(1.0f);  // Identity matrix

        // Calculate the position of the cube
        glm::vec3 position =
            glm::vec3(0.0f, 0.0f, i * 1.0f);  // Move cubes along the x-axis

        // Apply translation
        model = glm::translate(model, position);

        // Send the model matrix to your shader
        glUniformMatrix4fv(model_matrix_location, 1, GL_FALSE,
                           glm::value_ptr(model));

        this->draw_block();
    }

    for (unsigned int i = 0; i < cube_number; i++) {
        glm::mat4 model = glm::mat4(1.0f);  // Identity matrix

        // Calculate the position of the cube
        glm::vec3 position =
            glm::vec3(0.0f, i * 1.0f, 0.0f);  // Move cubes along the x-axis

        // Apply translation
        model = glm::translate(model, position);

        // Send the model matrix to your shader
        glUniformMatrix4fv(model_matrix_location, 1, GL_FALSE,
                           glm::value_ptr(model));

        this->draw_block();
    }
}
