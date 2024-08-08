#include <SDL2/SDL.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_video.h>
#include "Camera.hpp"
#include "ScreenSize.hpp"
#include "should_close_window.hpp"

void input_handler(Camera *camera, const ScreenSize &screen,
                   SDL_Window *window) {
    static int mouseXpos = screen.width / 2;
    static int mouseYpos = screen.height / 2;

    SDL_Event event;

    const Uint8 *state = SDL_GetKeyboardState(NULL);

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_MOUSEMOTION:
                if (SDL_GetRelativeMouseMode() == SDL_FALSE) {
                    break;
                }
                mouseXpos += event.motion.xrel;
                mouseYpos += event.motion.yrel;
                camera->mouse_look(mouseXpos, mouseYpos);
                break;
            case SDL_KEYDOWN: {
                if (state[SDL_SCANCODE_ESCAPE]) {
                    if (event.key.repeat) {
                        break;
                    }

                    const SDL_bool is_mouse_relative_mode =
                        SDL_GetRelativeMouseMode();

                    if (is_mouse_relative_mode) {
                        SDL_WarpMouseInWindow(window, screen.width / 2,
                                              screen.height / 2);
                    }

                    SDL_SetRelativeMouseMode(is_mouse_relative_mode ? SDL_FALSE
                                                                    : SDL_TRUE);
                }
                break;
            }
            case SDL_QUIT:
                should_close_window = true;
                break;
            default:
                break;
        }
    }

    static Uint8 window_flags = SDL_GetWindowFlags(window);
    static bool is_fullscreen_window = window_flags & SDL_WINDOW_FULLSCREEN;

    const static float cameraSpeed = 0.2f;

    if (state[SDL_SCANCODE_W]) {
        camera->move_forward(cameraSpeed);
    }
    if (state[SDL_SCANCODE_A]) {
        camera->move_left(cameraSpeed);
    }
    if (state[SDL_SCANCODE_S]) {
        camera->move_backward(cameraSpeed);
    }
    if (state[SDL_SCANCODE_D]) {
        camera->move_right(cameraSpeed);
    }
    if (state[SDL_SCANCODE_F]) {
        camera->move_up(cameraSpeed);
    }
    // TODO: use SHIFT + f instead of g
    if (state[SDL_SCANCODE_G]) {
        camera->move_down(cameraSpeed);
    }

    // broken af
    /*if (state[SDL_SCANCODE_F11]) {*/
    /*    SDL_SetWindowFullscreen(window,*/
    /*                            is_fullscreen_window ? SDL_FALSE :
     * SDL_TRUE);*/
    /*    is_fullscreen_window = !is_fullscreen_window;*/
    /*}*/
}
