#pragma once

#include <string>
#include "glad.h"

GLuint create_graphics_pipeline(const std::string shadersDirectory,
                              const std::string fragmentShaderFileName,
                              const std::string vertexShaderFileName);

GLuint create_shader_program(const std::string &vertexShaderSource,
                           const std::string &fragmentShaderSource);

GLuint compile_shader(GLuint type, const std::string &src);

std::string load_shader(const std::string &filePath);
