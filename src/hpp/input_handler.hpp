#pragma once

#include <SDL2/SDL_video.h>
#include "Camera.hpp"
#include "ScreenSize.hpp"

void input_handler(Camera *camera, const ScreenSize &screen, SDL_Window *window);
