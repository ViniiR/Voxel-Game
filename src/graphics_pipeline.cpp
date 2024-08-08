#include <fstream>
#include <string>
#include <iostream>
#include "glad.h"
#include "graphics_pipeline.hpp"

GLuint create_graphics_pipeline(const std::string shadersDirectory,
                                const std::string fragmentShaderFileName,
                                const std::string vertexShaderFileName) {
    static const std::string vertexShaderSource =
        load_shader(shadersDirectory + vertexShaderFileName);
    static const std::string fragmentShaderSource =
        load_shader(shadersDirectory + fragmentShaderFileName);

    return create_shader_program(vertexShaderSource, fragmentShaderSource);
}

const std::string load_shader(const std::string &filePath) {
    std::string result = "";

    std::string line = "";
    std::ifstream file(filePath.c_str());

    if (file.is_open()) {
        while (std::getline(file, line)) {
            result += line + '\n';
        }
        file.close();
    }
    return result;
}

GLuint create_shader_program(const std::string &vertexShaderSource,
                             const std::string &fragmentShaderSource) {
    const GLuint programObj = glCreateProgram();

    const GLuint vertexShader =
        compile_shader(GL_VERTEX_SHADER, vertexShaderSource);
    const GLuint fragmentShader =
        compile_shader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    glAttachShader(programObj, vertexShader);
    glAttachShader(programObj, fragmentShader);

    glLinkProgram(programObj);
    glValidateProgram(programObj);

    return programObj;
}

GLuint compile_shader(GLuint type, const std::string &src) {
    GLuint shaderObj;
    switch (type) {
        case GL_VERTEX_SHADER:
            shaderObj = glCreateShader(GL_VERTEX_SHADER);
            break;
        case GL_FRAGMENT_SHADER:
            shaderObj = glCreateShader(GL_FRAGMENT_SHADER);
            break;
        default:
            std::cerr << "invalid GLuint enum variant on compileShader"
                      << std::endl;
            exit(-1);
    }
    const char *source = src.c_str();
    glShaderSource(shaderObj, 1, &source, nullptr);
    glCompileShader(shaderObj);

    return shaderObj;
}
