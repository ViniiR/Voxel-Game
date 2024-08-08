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
#include <string>
#include <vector>
#include <cstdlib>
#include <glad.h>
#include "Camera.hpp"
#include "ScreenSize.hpp"
/*#include "cube.hpp"*/
#include "graphics_pipeline.hpp"
#include "input_handler.hpp"
#include "should_close_window.hpp"
#include "drawing.hpp"

void window_loop();
void init_program();
void destroy_program();

void vertexSpecification();

SDL_Window *window = nullptr;

bool should_close_window = false;
GLuint graphics_pipeline_shader_program = 0;
GLuint vertex_array_object = 0;
GLuint vertex_buffer_object = 0;
GLuint index_buffer_object = 0;

const std::string shaders_directory = "../shaders/";
const std::string fragment_shader_filename = "fragment.glsl";
const std::string vertex_shader_filename = "vertex.glsl";

ScreenSize screen = {
    720,  // height
    1280  // width
};

Camera *camera = new Camera();

int init_SDL() {
    init_program();

    vertexSpecification();

    graphics_pipeline_shader_program = create_graphics_pipeline(
        shaders_directory, fragment_shader_filename, vertex_shader_filename);

    window_loop();

    destroy_program();

    return 0;
}

void init_program() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        exit(-1);
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
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

    glEnable(GL_DEPTH_TEST);
    SDL_SetRelativeMouseMode(SDL_TRUE);

    SDL_GL_SetSwapInterval(1);
}

void destroy_program() {
    SDL_DestroyWindow(window);
    SDL_Quit();
    delete camera;
}

void window_loop() {
    SDL_WarpMouseInWindow(window, screen.width / 2, screen.height / 2);

    while (!should_close_window) {
        input_handler(camera, screen, window);

        pre_draw(camera, screen, graphics_pipeline_shader_program);

        draw(vertex_array_object);

        SDL_GL_SwapWindow(window);
    }
}

void vertexSpecification() {
    static const std::vector<GLfloat> vertexData = {
        // Vertex - 0
        // x     y     z
        -0.5f, -0.5f, 0.0f,  // Bottom Left Vertex position
        1.0f, 0.0f, 0.0f,    // RGB color
        // R     G     B
        //
        // Vertex - 1
        // x     y     z
        0.5f, -0.5f, 0.0f,  // Bottom Right Vertex position
        0.0f, 1.0f, 0.0f,   // RGB color
        // R     G     B
        //
        // Vertex - 2
        // x     y     z
        -0.5f, 0.5f, 0.0f,  // Top Left Vertex position
        0.0f, 0.0f, 1.0f,   // RGB color
        // R     G     B
        //
        // x     y     z
        /*0.5f, -0.5f, 0.0f,  // Bottom Right Vertex position*/
        /*0.0f, 1.0f, 0.0f,  // RGB color*/
        // R     G     B
        //
        // Vertex - 3
        // x     y     z
        0.5f, 0.5f, 0.0f,  // Top Right Vertex position
        1.0f, 0.0f, 0.0f,  // RGB color
        // R     G     B
        //
        // x     y     z
        /*-0.5f, 0.5f, 0.0f,  // Top Left Vertex position*/
        /*0.0f, 0.0f, 1.0f,   // RGB color*/
        // R     G     B
    };
    // drawing cuz ima dumbass:
    // 2 & 2----------------1
    // |\\                  |
    // |  \\                |
    // |    \\              |
    // |      \\            |
    // |        \\\\        |
    // |            \\      |
    // |              \\    |
    // |                \\  |
    // |                  \\|
    // 0--------------------1 & 0

    const std::vector<GLuint> indexBufferData = {
        //
        2, 0, 1,  //
        3, 2, 1   //
    };
    glGenVertexArrays(1, &vertex_array_object);
    glBindVertexArray(vertex_array_object);
    glGenBuffers(1, &vertex_buffer_object);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
    glBufferData(GL_ARRAY_BUFFER,
                 vertexData.size() * sizeof(GLfloat),  //
                 vertexData.data(), GL_STATIC_DRAW);

    //

    // position information
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,
                          3,                    //
                          GL_FLOAT, GL_FALSE,   //
                          sizeof(GLfloat) * 6,  //
                          (GLvoid *)0);
    // color information
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,
                          3,                    //
                          GL_FLOAT, GL_FALSE,   //
                          sizeof(GLfloat) * 6,  //
                          (GLvoid *)(sizeof(GLfloat) * 3));

    // Gen IBO
    glGenBuffers(1, &index_buffer_object);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_object);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 indexBufferData.size() * sizeof(GLuint),  //
                 indexBufferData.data(),                   //
                 GL_STATIC_DRAW                            //
    );

    // bind vertex array where? (learn)
    glBindVertexArray(0);

    // post binding (cleanup)
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}
