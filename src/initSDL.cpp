#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_video.h>
#include <cstdlib>
#include <fstream>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/trigonometric.hpp>
#include <glm/vec3.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <glad.h>
#include "./hpp/Camera.hpp"

int windowLoop();
void initProgram();
int destroyProgram();
void handleInput();
void vertexSpecification();
void createGraphicsPipeline();
void preDraw();
void draw();
const std::string loadShader(const std::string &filePath);
GLuint createShaderProgram(const std::string &vertexShaderSource,
                           const std::string &fragmentShaderSource);
GLuint compileShader(GLuint type, const std::string &src);

SDL_Window *window = nullptr;
bool shouldCloseWindow = false;
GLuint graphicsPipelineShaderProgram = 0;
static GLuint vertexArrayObject = 0;
static GLuint vertexBufferObject = 0;
static GLuint indexBufferObject = 0;
static const int screenH = 720;
static const int screenW = 1280;
static const std::string shadersDirectory = "../shaders/";
static const std::string fragmentShaderFileName = "fragment.glsl";
static const std::string vertexShaderFileName = "vertex.glsl";
Camera camera;

int initSDL() {
    initProgram();

    vertexSpecification();

    createGraphicsPipeline();

    windowLoop();

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

    const SDL_GLContext context = SDL_GL_CreateContext(window);
    if (context == nullptr) {
        exit(-1);
    }

    // init glad lib
    if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
        exit(-1);
    }

    glEnable(GL_DEPTH_TEST);

    SDL_GL_SetSwapInterval(1);
}

int destroyProgram() {
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

int windowLoop() {
    SDL_WarpMouseInWindow(window, screenW / 2, screenH / 2);
    SDL_SetRelativeMouseMode(SDL_TRUE);

    while (!shouldCloseWindow) {
        handleInput();

        preDraw();

        draw();

        SDL_GL_SwapWindow(window);
    }

    return 0;
}

void handleInput() {
    static int mouseXpos = screenW / 2;
    static int mouseYpos = screenH / 2;

    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN:
                /*std::cout << event.key.type;*/
                // case F11 pressed set !isFullscreen
                /*SDL_SetWindowFullscreen(window,
                 * SDL_WINDOW_FULLSCREEN_DESKTOP);*/
                break;

            case SDL_MOUSEMOTION:
                mouseXpos += event.motion.xrel;
                mouseYpos += event.motion.yrel;
                camera.mouseLook(mouseXpos, mouseYpos);
                break;
            case SDL_QUIT:
                shouldCloseWindow = true;
                break;
        }
    }

    const Uint8 *state = SDL_GetKeyboardState(NULL);
    const static float cameraSpeed = 0.01f;
    if (state[SDL_SCANCODE_W]) {
        camera.moveForward(cameraSpeed);
    }
    if (state[SDL_SCANCODE_A]) {
        camera.moveLeft(cameraSpeed);
    }
    if (state[SDL_SCANCODE_S]) {
        camera.moveBackward(cameraSpeed);
    }
    if (state[SDL_SCANCODE_D]) {
        camera.moveRight(cameraSpeed);
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
    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);
    glGenBuffers(1, &vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
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
    glGenBuffers(1, &indexBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);
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

void createGraphicsPipeline() {
    static const std::string vertexShaderSource =
        loadShader(shadersDirectory + vertexShaderFileName);
    static const std::string fragmentShaderSource =
        loadShader(shadersDirectory + fragmentShaderFileName);

    graphicsPipelineShaderProgram =
        createShaderProgram(vertexShaderSource, fragmentShaderSource);
}

GLuint createShaderProgram(const std::string &vertexShaderSource,
                           const std::string &fragmentShaderSource) {
    const GLuint programObj = glCreateProgram();

    const GLuint vertexShader =
        compileShader(GL_VERTEX_SHADER, vertexShaderSource);
    const GLuint fragmentShader =
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

    //

    const GLint uniformModelMatrixLocation =  //
        glGetUniformLocation(                 //
            graphicsPipelineShaderProgram,    //
            "uModelMatrix"                    //
        );
    if (uniformModelMatrixLocation == -1) {
        std::cerr << "model matrix location not found" << std::endl;
        exit(-1);
    }

    // in case a square is not seen: the translation.z is 0 which means it is
    // inside the camera, below the minimal viewable distance of 0.1
    const glm::mat4 translate =
        glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -10.0f));
    glUniformMatrix4fv(uniformModelMatrixLocation, 1, GL_FALSE,
                       &translate[0][0]);

    //

    glm::mat4 view = camera.getViewMatrix();
    const GLint uniformViewMatrixLocation =  //
        glGetUniformLocation(                //
            graphicsPipelineShaderProgram,   //
            "uViewMatrix"                    //
        );
    if (uniformViewMatrixLocation == -1) {
        std::cerr << "uniform viewMatrix location location not found"
                  << std::endl;
        exit(-1);
    }
    glUniformMatrix4fv(uniformViewMatrixLocation, 1, GL_FALSE, &view[0][0]);

    //

    const GLint uniformProjectionLocation =  //
        glGetUniformLocation(                //
            graphicsPipelineShaderProgram,   //
            "uProjection"                    //
        );
    if (uniformProjectionLocation == -1) {
        std::cerr << "uniform uProjection location not found" << std::endl;
        exit(-1);
    }

    // how close and far you can see at: 3rd n 4th params
    const glm::mat4 perspective = glm::perspective(
        glm::radians(45.0f), (float)screenW / (float)screenH, 0.1f, 100.0f);
    glUniformMatrix4fv(uniformProjectionLocation, 1, GL_FALSE,
                       &perspective[0][0]);
}

void draw() {
    glBindVertexArray(vertexArrayObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

const std::string loadShader(const std::string &filePath) {
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
