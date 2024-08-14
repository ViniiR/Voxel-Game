#include <cstdlib>
#include <fstream>
#include <string>
#include <iostream>
#include "glad.h"
#include "graphics_pipeline.hpp"

GLuint create_graphics_pipeline(const std::string shaders_dir,
                                const std::string fragment_shader_filename,
                                const std::string vertex_shader_filename) {
    static const std::string vertex_shader_source_path =
        load_shader(shaders_dir + vertex_shader_filename);
    static const std::string fragment_shader_source_path =
        load_shader(shaders_dir + fragment_shader_filename);

    return create_shader_program(vertex_shader_source_path,
                                 fragment_shader_source_path);
}

std::string load_shader(const std::string &filePath) {
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

// for some dumb shit ass reason opengl throws 1282 if i call this function no
// matter if its success or not
/*enum GLuintObjectType { VertexShader, FragmentShader, Program };*/
/**/
/*bool validate_gluint_object(GLuintObjectType type, const GLuint obj) {*/
/*    GLint success = 0;*/
/*    GLchar info_log[512];*/
/**/
/*    switch (type) {*/
/*        case VertexShader:*/
/*            glGetShaderiv(obj, GL_COMPILE_STATUS, &success);*/
/*            if (!success) {*/
/*                glGetShaderInfoLog(obj, 512, nullptr, info_log);*/
/*                std::cout << "error loading vertex_shader" << std::endl;*/
/*            }*/
/*        case FragmentShader:*/
/*            glGetShaderiv(obj, GL_COMPILE_STATUS, &success);*/
/*            if (!success) {*/
/*                glGetShaderInfoLog(obj, 512, nullptr, info_log);*/
/*                std::cout << "error loading vertex_shader" << std::endl;*/
/*            }*/
/*        case Program:*/
/*            glGetProgramiv(obj, GL_LINK_STATUS, &success);*/
/*            if (!success) {*/
/*                glGetProgramInfoLog(obj, 512, nullptr, info_log);*/
/*                std::cerr << "error linking shader program" << std::endl;*/
/*            }*/
/*    }*/
/*    return success != 0 ? true : false;*/
/*}*/

GLuint create_shader_program(const std::string &vertex_shader_source,
                             const std::string &fragment_shader_source) {
    const GLuint program_object = glCreateProgram();
    GLint success;
    GLchar info_log[512];

    const GLuint vertex_shader =
        compile_shader(GL_VERTEX_SHADER, vertex_shader_source);
    const GLuint fragment_shader =
        compile_shader(GL_FRAGMENT_SHADER, fragment_shader_source);

    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        std::cout << "OpenGL error on shader object:" << info_log << std::endl;
        exit(-1);
    }

    glAttachShader(program_object, vertex_shader);
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << "attaching vertex shader error: " << err << std::endl;
        exit(-1);
    }
    glAttachShader(program_object, fragment_shader);
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << "attaching fragment shader error: " << err << std::endl;
        exit(-1);
    }

    glLinkProgram(program_object);

    glGetProgramiv(program_object, GL_LINK_STATUS, &success);
    glValidateProgram(program_object);

    if (!success) {
        std::cout << "OpenGL error on program linking:" << info_log << std::endl;
        exit(-1);
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return program_object;
}

GLuint compile_shader(GLuint type, const std::string &src) {
    GLuint shader_object;
    switch (type) {
        case GL_VERTEX_SHADER:
            shader_object = glCreateShader(GL_VERTEX_SHADER);
            break;
        case GL_FRAGMENT_SHADER:
            shader_object = glCreateShader(GL_FRAGMENT_SHADER);
            break;
        default:
            std::cerr << "invalid GLuint enum variant on compileShader"
                      << std::endl;
            exit(-1);
    }
    const char *source = src.c_str();
    glShaderSource(shader_object, 1, &source, nullptr);
    glCompileShader(shader_object);

    return shader_object;
}
