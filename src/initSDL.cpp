#include "hpp/initSDL.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_opengl.h>
#include <GL/gl.h>

GLfloat vertices[] = {
    // x, y, z
    -0.5f, -0.5f, 0.0f,  // Bottom left
    0.5f,  -0.5f, 0.0f,  // Bottom right
    0.0f,  0.5f,  0.0f   // Top
};

bool initSDL() {
    int screenW = 800;
    int screenH = 600;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        return false;
    }
    SDL_Window* window = SDL_CreateWindow(
        "V9.9", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenW,
        screenH, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (!window) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }

    SDL_GLContext context = SDL_GL_CreateContext(window);
    if (!context) {
        return false;
    }

    unsigned int VBO;
    /*gl*/

    bool quit = false;
    while (!quit) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_KEYDOWN:
                    /*std::cout << event.key.type;*/
                    break;
                case SDL_QUIT:
                    quit = true;
                    break;
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return true;
}
