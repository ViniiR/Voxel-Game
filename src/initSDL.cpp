#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_video.h>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "../glad/glad.h"

int wndLoop();
void initProgram();
int destroyProgram();
void handleInput();
void vertexSpecification();
void createGraphicsPipeline();
void preDraw();
void draw();
std::string loadShader(const std::string &filePath);
GLuint createShaderProgram(const std::string &vertexShaderSource,
                           const std::string &fragmentShaderSource);
GLuint compileShader(GLuint type, const std::string &src);

SDL_Window *window = nullptr;
bool shouldCloseWindow = false;
GLuint graphicsPipelineShaderProgram = 0;
GLuint vertexArrayObject = 0;
GLuint vertexBufferObject = 0;
GLuint vertexBufferObject2 = 0;
const int screenW = 800;
const int screenH = 600;
const std::string shadersDirectory = "../shaders/";
const std::string fragmentShaderFileName = "fragment.glsl";
const std::string vertexShaderFileName = "vertex.glsl";

int initSDL() {
    initProgram();

    vertexSpecification();

    createGraphicsPipeline();

    wndLoop();

    return destroyProgram();
}

void initProgram() {
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

    window = SDL_CreateWindow(
        "V9.9", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenW,
        screenH, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (!window) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        exit(-1);
    }

    SDL_GLContext context = SDL_GL_CreateContext(window);
    if (context == nullptr) {
        exit(-1);
    }

    // init glad lib
    if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
        exit(-1);
    }

    SDL_GL_SetSwapInterval(1);
}

int destroyProgram() {
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

int wndLoop() {
    while (!shouldCloseWindow) {
        preDraw();

        draw();

        handleInput();

        SDL_GL_SwapWindow(window);
    }

    return 0;
}

void handleInput() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN:
                /*std::cout << event.key.type;*/
                // case F11 pressed set !isFullscreen
                /*SDL_SetWindowFullscreen(window,
                 * SDL_WINDOW_FULLSCREEN_DESKTOP);*/
                break;
            case SDL_QUIT:
                shouldCloseWindow = true;
                break;
        }
    }
}

void vertexSpecification() {
    const std::vector<GLfloat> vertexPositions = {
        -0.5f, -0.5f, 0.0f,  //
        0.5f,  -0.5f, 0.0f,  //
        0.0f,  0.5f,  0.0f,  //
    };
    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);
    glGenBuffers(1, &vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER,
                 vertexPositions.size() * sizeof(GLfloat),  //
                 vertexPositions.data(), GL_STATIC_DRAW);

    //

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,
                          3,  // X Y Z
                          GL_FLOAT, GL_FALSE, 0, (void *)0);

    //

    const std::vector<GLfloat> vertexColors = {
        1.0f, 0.0f, 0.0f,  //
        0.0f, 1.0f, 0.0f,  //
        0.0f, 0.0f, 1.0f,  //
    };
    glGenBuffers(1, &vertexBufferObject2);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject2);
    glBufferData(GL_ARRAY_BUFFER,
                 vertexColors.size() * sizeof(GLfloat),  //
                 vertexColors.data(), GL_STATIC_DRAW);

    //

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,
                          3,  // RGB
                          GL_FLOAT, GL_FALSE, 0, (void *)0);

    // bind vertex array where? (learn)
    glBindVertexArray(0);

    // post binding (cleanup)
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

void createGraphicsPipeline() {
    const std::string vertexShaderSource =
        loadShader(shadersDirectory + vertexShaderFileName);
    const std::string fragmentShaderSource =
        loadShader(shadersDirectory + fragmentShaderFileName);

    graphicsPipelineShaderProgram =
        createShaderProgram(vertexShaderSource, fragmentShaderSource);
}

GLuint createShaderProgram(const std::string &vertexShaderSource,
                           const std::string &fragmentShaderSource) {
    GLuint programObj = glCreateProgram();

    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
    GLuint fragmentShader =
        compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    glAttachShader(programObj, vertexShader);
    glAttachShader(programObj, fragmentShader);

    glLinkProgram(programObj);
    glValidateProgram(programObj);

    return programObj;
}

GLuint compileShader(GLuint type, const std::string &src) {
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

void preDraw() {
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    glViewport(0, 0, screenW, screenH);
    glClearColor(1.f, 1.f, 1.f, 1.f);

    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    glUseProgram(graphicsPipelineShaderProgram);
}

void draw() {
    glBindVertexArray(vertexArrayObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);

    glDrawArrays(GL_TRIANGLES, 0, 3);
}

std::string loadShader(const std::string &filePath) {
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
