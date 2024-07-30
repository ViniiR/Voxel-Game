#include <SDL2/SDL_main.h>
#include <cstdio>
#include <iostream>
#include "src/hpp/initSDL.hpp"

//std::cout works on: g++ Windows
//works on cl.exe(msvs compiler)
//does NOT work when using CMake
//TODO: test with minimal CMake setup
int main(int argc, char* argv[]) {
    std::cout << "puta que pariu" << std::endl;
    puts("porra");
    printf("👍👍👍👍👍👍👍👍👍");

    return initSDL();
}
