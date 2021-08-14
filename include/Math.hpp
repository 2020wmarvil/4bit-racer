#ifndef MATH
#define MATH

#include <cmath>

class Vector2 {
public:
    float x;
    float y;

    Vector2(float x, float y) {
        this->x = x;
        this->y = y;
    }
};

float DegreesToRadians(float degrees) {
    return degrees * M_PI / 180;
}

float RadiansToDegrees(float radians) {
    return radians * 180 / M_PI;
}

#endif