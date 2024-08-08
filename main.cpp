#include <SDL2/SDL_main.h>
#include <cstdio>
#include <iostream>
#include "init_SDL.hpp"

//std::cout works on: g++ Windows
//works on cl.exe(msvs compiler)
//does NOT work when using CMake
//TODO: test with minimal CMake setup
int main(int argc, char* argv[]) {
    std::cout << "no output" << std::endl;
    puts("no output");
    printf("👍👍👍👍👍👍👍👍👍");

    return init_SDL();
}
