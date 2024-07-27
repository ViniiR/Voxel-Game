#include "hpp/vector3d.hpp"

vector3d::vector3d() {
    x = 0;
    y = 0;
    z = 0;
}

vector3d::vector3d(float a, float b) {
    x = a;
    y = b;
    z = 0;
}

vector3d::vector3d(float a, float b, float c) {
    x = a;
    y = b;
    z = c;
}
