#pragma once

#include <iostream>
#include <cmath>

class vector3d {
   public:
    float x = 0;
    float y = 0;
    float z = 0;

    vector3d();
    vector3d(float a, float b);
    vector3d(float a, float b, float c);

    float lenght();
    void normalize();

    void change(float a, float b, float c);
    void change(vector3d& vec);
    void change(vector3d vec);

    void changeX(float a);
    void changeY(float a);
    void changeZ(float a);

    vector3d operator+(const vector3d& vec);
    vector3d operator-(const vector3d& vec);
    vector3d operator*(float a);
    vector3d operator/(float a);

    vector3d& operator+=(const vector3d& vec);
    vector3d& operator-=(const vector3d& vec);
    vector3d& operator*=(float a);
    vector3d& operator/=(float a);

    bool operator==(const vector3d vec);
    bool operator!=(const vector3d vec);

    friend std::ostream& operator<<(std::ostream& out, vector3d& vec);

    /*float dotProduct(const vector3d& vec);*/
    /*vector3d crossProduct(const vector3d& vec);*/
};
