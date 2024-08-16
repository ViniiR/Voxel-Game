#pragma once

#include "glad.h"
#include <string>
enum CubeFace { Front, Back, Right, Left, Top, Bottom };

GLuint cube_specification(GLuint VAO, GLuint VBO, GLuint EBO);
void draw_cube_face(GLuint VAO, std::string face_texture_path,
                    CubeFace face_position, GLuint EBO);
