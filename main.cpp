#include <SDL2/SDL_main.h>
#include "src/hpp/initSDL.hpp"

int main(int argc, char* argv[]) {
    if (!initSDL()) {
        return -1;
    }
    return 0;
}
