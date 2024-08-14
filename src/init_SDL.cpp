#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_video.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/trigonometric.hpp>
#include <glm/vec3.hpp>
#include <iostream>
#include <string>
#include <cstdlib>
#include <glad.h>
#include "Camera.hpp"
#include "ScreenSize.hpp"
#include "cube.hpp"
#include "graphics_pipeline.hpp"
#include "input_handler.hpp"
#include "should_close_window.hpp"
#include "drawing.hpp"

void window_loop(GLuint program, GLuint VAO, GLuint vertices_VBO);
void init_program();
void destroy_program();

SDL_Window *window = nullptr;

bool should_close_window = false;

const std::string shaders_directory = "../shaders/";
const std::string fragment_shader_filename = "fragment.glsl";
const std::string vertex_shader_filename = "vertex.glsl";

ScreenSize screen = {
    720,  // height
    1280  // width
};

Camera *camera = new Camera();

GLuint better_cube(GLuint VAO, GLuint VBO, GLuint EBO) {
    float vertices[] = {
        // Positions         // Colors
        -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,  // Vertex 0
        0.5f,  -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,  // Vertex 1
        0.5f,  0.5f,  -0.5f, 0.0f, 0.0f, 1.0f,  // Vertex 2
        -0.5f, 0.5f,  -0.5f, 1.0f, 1.0f, 0.0f,  // Vertex 3
        -0.5f, -0.5f, 0.5f,  1.0f, 0.0f, 1.0f,  // Vertex 4
        0.5f,  -0.5f, 0.5f,  0.0f, 1.0f, 1.0f,  // Vertex 5
        0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f,  // Vertex 6
        -0.5f, 0.5f,  0.5f,  0.0f, 0.0f, 0.0f   // Vertex 7
    };
    unsigned int indices[] = {// Front face
                              0, 1, 2, 2, 3, 0,

                              // Back face
                              4, 5, 6, 6, 7, 4,

                              // Left face
                              0, 3, 7, 7, 4, 0,

                              // Right face
                              1, 5, 6, 6, 2, 1,

                              // Top face
                              3, 2, 6, 6, 7, 3,

                              // Bottom face
                              0, 1, 5, 5, 4, 0};
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
                 GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);

    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    return VAO;
}

int init_SDL() {
    static GLuint graphics_pipeline_shader_program = 0;
    static GLuint VAO = 0;
    static GLuint vertices_VBO = 0;
    static GLuint color_VBO = 0;
    static GLuint EBO = 0;

    init_program();

    /*VAO = cube_specification(vertices_VBO, VAO, color_VBO);*/
    VAO = better_cube(VAO, vertices_VBO, EBO);

    graphics_pipeline_shader_program = create_graphics_pipeline(
        shaders_directory, fragment_shader_filename, vertex_shader_filename);

    window_loop(graphics_pipeline_shader_program, VAO, vertices_VBO);

    destroy_program();

    return 0;
}

void init_program() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        exit(-1);
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE);

    window =
        SDL_CreateWindow("V9.9", SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED, screen.width, screen.height,
                         SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL |
                             SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);
    if (!window) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        exit(-1);
    }

    const SDL_GLContext context = SDL_GL_CreateContext(window);
    if (context == nullptr) {
        exit(-1);
    }

    if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
        exit(-1);
    }

    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

    glEnable(GL_DEPTH_TEST);
    SDL_SetRelativeMouseMode(SDL_TRUE);

    SDL_GL_SetSwapInterval(1);
}

void destroy_program() {
    SDL_DestroyWindow(window);
    SDL_Quit();
    delete camera;
}

void window_loop(GLuint program, GLuint VAO, GLuint vertices_VBO) {
    SDL_WarpMouseInWindow(window, screen.width / 2, screen.height / 2);

    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << "pre Window Loop error: " << err << std::endl;
        exit(-1);
    }

    while (!should_close_window) {
        input_handler(camera, screen, window);

        pre_draw(camera, screen, program);

        draw(VAO, vertices_VBO);

        SDL_GL_SwapWindow(window);
    }
}
