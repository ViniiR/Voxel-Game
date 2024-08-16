#pragma once

#include <cube.hpp>
#include <string>
#include "glad.h"

#include <string>

struct BlockTextures {
        std::string multi_face_texture;

        std::string right_face_texture;
        std::string left_face_texture;
        std::string top_face_texture;
        std::string bottom_face_texture;
        std::string back_face_texture;
        std::string front_face_texture;

        BlockTextures(const std::string& multi_face_texture,
                      const std::string& right_face_texture,
                      const std::string& left_face_texture,
                      const std::string& front_face_texture,
                      const std::string& back_face_texture,
                      const std::string& top_face_texture,
                      const std::string& bottom_face_texture)
            : multi_face_texture(multi_face_texture),
              right_face_texture(right_face_texture),
              left_face_texture(left_face_texture),
              top_face_texture(top_face_texture),
              bottom_face_texture(bottom_face_texture),
              back_face_texture(back_face_texture),
              front_face_texture(front_face_texture) {}
};

extern BlockTextures GrassTextures;

class VirtualBlock {
    protected:
        virtual GLuint get_VAO() const = 0;
        virtual GLuint get_EBO() const = 0;

        virtual std::string get_multi_face_texture() const = 0;

        virtual std::string get_right_face_texture() const = 0;
        virtual std::string get_left_face_texture() const = 0;
        virtual std::string get_top_face_texture() const = 0;
        virtual std::string get_bottom_face_texture() const = 0;
        virtual std::string get_back_face_texture() const = 0;
        virtual std::string get_front_face_texture() const = 0;

    public:
        virtual ~VirtualBlock() = default;

        void draw_block() const {
            draw_back_face();
            draw_front_face();
            draw_right_face();
            draw_left_face();
            draw_top_face();
            draw_bottom_face();
        }

        void draw_back_face() const {
            const auto back_face_texture = get_back_face_texture();
            const auto multi_face_texture = get_multi_face_texture();
            const auto EBO = get_EBO();
            const auto VAO = get_VAO();
            if (back_face_texture.empty()) {
                draw_cube_face(VAO, multi_face_texture, Back, EBO);
                return;
            }
            draw_cube_face(VAO, back_face_texture, Back, EBO);
        }
        void draw_front_face() const {
            const auto front_face_texture = get_front_face_texture();
            const auto multi_face_texture = get_multi_face_texture();
            const auto EBO = get_EBO();
            const auto VAO = get_VAO();
            if (front_face_texture.empty()) {
                draw_cube_face(VAO, multi_face_texture, Front, EBO);
                return;
            }
            draw_cube_face(VAO, front_face_texture, Front, EBO);
        }
        void draw_left_face() const {
            const auto left_face_texture = get_left_face_texture();
            const auto multi_face_texture = get_multi_face_texture();
            const auto EBO = get_EBO();
            const auto VAO = get_VAO();
            if (left_face_texture.empty()) {
                draw_cube_face(VAO, multi_face_texture, Left, EBO);
                return;
            }
            draw_cube_face(VAO, left_face_texture, Left, EBO);
        }
        void draw_right_face() const {
            const auto right_face_texture = get_right_face_texture();
            const auto multi_face_texture = get_multi_face_texture();
            const auto EBO = get_EBO();
            const auto VAO = get_VAO();
            if (right_face_texture.empty()) {
                draw_cube_face(VAO, multi_face_texture, Right, EBO);
                return;
            }
            draw_cube_face(VAO, right_face_texture, Right, EBO);
        }
        void draw_top_face() const {
            const auto top_face_texture = get_top_face_texture();
            const auto multi_face_texture = get_multi_face_texture();
            const auto EBO = get_EBO();
            const auto VAO = get_VAO();
            if (top_face_texture.empty()) {
                draw_cube_face(VAO, multi_face_texture, Top, EBO);
                return;
            }
            draw_cube_face(VAO, top_face_texture, Top, EBO);
        }
        void draw_bottom_face() const {
            const auto bottom_face_texture = get_bottom_face_texture();
            const auto multi_face_texture = get_multi_face_texture();
            const auto EBO = get_EBO();
            const auto VAO = get_VAO();
            if (bottom_face_texture.empty()) {
                draw_cube_face(VAO, multi_face_texture, Bottom, EBO);
                return;
            }
            draw_cube_face(VAO, bottom_face_texture, Bottom, EBO);
        }
};

class Block : public VirtualBlock {
    public:
        Block(GLuint VAO, GLuint EBO, BlockTextures textures);

        void tmp_draw_lottacubes(GLuint shader_program,
                                unsigned int cube_number);

        GLuint VAO;
        GLuint EBO;

        std::string multi_face_texture;

        std::string right_face_texture;
        std::string left_face_texture;
        std::string top_face_texture;
        std::string bottom_face_texture;
        std::string back_face_texture;
        std::string front_face_texture;

        GLuint get_VAO() const override { return VAO; }
        GLuint get_EBO() const override { return EBO; }

        std::string get_multi_face_texture() const override {
            return multi_face_texture;
        }

        std::string get_right_face_texture() const override {
            return right_face_texture;
        }
        std::string get_left_face_texture() const override {
            return left_face_texture;
        }
        std::string get_top_face_texture() const override {
            return top_face_texture;
        }
        std::string get_bottom_face_texture() const override {
            return bottom_face_texture;
        }
        std::string get_back_face_texture() const override {
            return back_face_texture;
        }
        std::string get_front_face_texture() const override {
            return front_face_texture;
        }
};
