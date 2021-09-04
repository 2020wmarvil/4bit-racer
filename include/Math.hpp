#ifndef MATH
#define MATH

#include <cmath>

//class Vector2 {
//public:
//    float x;
//    float y;
//
//    Vector2(float x, float y) {
//        this->x = x;
//        this->y = y;
//    }
//};

template<unsigned int I>
struct scalar_swizzle {
    float v[1];
    float &operator=(const float x) {
        v[I] = x;
        return v[I];
    }

    operator float() const {
        return v[I];
    }

    float operator++(int) {
        return v[I]++;
    }

    float operator++() {
        return ++v[I];
    }

    float operator--(int) {
        return v[I]--;
    }

    float operator--() {
        return --v[I];
    }
};

// We use a vec_type in a template instead of forward declartions to prevent erros in some compilers.
template<typename vec_type, unsigned int A, unsigned int B>
struct vec2_swizzle {
    float d[2];
    vec_type operator=(const vec_type& vec) {
        return vec_type(d[A] = vec.x, d[B] = vec.y);
    }

    operator vec_type() {
        return vec_type(d[A], d[B]);
    }
};

struct vec2 {
    union {
        float d[2];
        scalar_swizzle<0> x, i;
        scalar_swizzle<1> y, j;

        vec2_swizzle<vec2, 0, 0> xx;
        vec2_swizzle<vec2, 0, 1> xy;
        vec2_swizzle<vec2, 1, 0> yx;
        vec2_swizzle<vec2, 1, 1> yy;
    };

    vec2() {}

    vec2(float all) {
        x = y = all;
    }

    vec2(float a, float b) {
        x = a;
        y = b;
    }
};

inline std::ostream& operator<<(std::ostream &os, vec2 vec) {
    os << "(" << vec.x << ", " << vec.y << ")";
    return os;
}

float DegreesToRadians(float degrees) {
    return degrees * M_PI / 180;
}

float RadiansToDegrees(float radians) {
    return radians * 180 / M_PI;
}

#endif