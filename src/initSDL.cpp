#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_video.h>
#include "../glad/glad.h"

int wndLoop();
void handleInput();

SDL_Window *window = nullptr;
bool shouldCloseWindow = false;

int initSDL() {
    int screenW = 800;
    int screenH = 600;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        return -1;
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
        return -1;
    }

    SDL_GLContext context = SDL_GL_CreateContext(window);
    if (context == nullptr) {
        return -1;
    }

    //init glad lib
    if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
        return -1;
    }

    wndLoop();

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

int wndLoop() {
    while (!shouldCloseWindow) {
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
