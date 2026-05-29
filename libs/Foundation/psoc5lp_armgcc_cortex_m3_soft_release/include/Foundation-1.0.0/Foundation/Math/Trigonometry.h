#ifndef FOUNDATION_MATH_TRIGONOMETRY_H
#define FOUNDATION_MATH_TRIGONOMETRY_H

namespace Foundation {
    namespace Math {

        constexpr float Pi = 3.14159265358979323846f;

        constexpr float DegToRad(
            float degrees
        ) {
            return degrees * (Pi / 180.0f);
        }

        constexpr float RadToDeg(
            float radians
        ) {
            return radians * (180.0f / Pi);
        }

    }
}

#endif