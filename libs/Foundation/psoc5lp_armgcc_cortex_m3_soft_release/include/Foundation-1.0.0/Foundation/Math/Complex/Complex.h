#ifndef FOUNDATION_MATH_COMPLEX_H
#define FOUNDATION_MATH_COMPLEX_H

    #include <stdint.h>

    namespace Foundation {
    namespace Math {

        template <typename T>
        class Complex {
        public:

            T real;
            T imag;

            Complex();

            Complex(T real);

            Complex(
                T real,
                T imag
            );

            Complex(
                const Complex<T>& other
            );

            Complex<T>& operator=(
                const Complex<T>& other
            );

            Complex<T> operator+() const;

            Complex<T> operator-() const;

            Complex<T> operator+(
                const Complex<T>& other
            ) const;

            Complex<T> operator-(
                const Complex<T>& other
            ) const;

            Complex<T> operator*(
                const Complex<T>& other
            ) const;

            Complex<T> operator/(
                const Complex<T>& other
            ) const;

            Complex<T>& operator+=(
                const Complex<T>& other
            );

            Complex<T>& operator-=(
                const Complex<T>& other
            );

            Complex<T>& operator*=(
                const Complex<T>& other
            );

            Complex<T>& operator/=(
                const Complex<T>& other
            );

            bool operator==(
                const Complex<T>& other
            ) const;

            bool operator!=(
                const Complex<T>& other
            ) const;

            Complex<T> Conjugate() const;

            T MagnitudeSquared() const;
        };

    } // namespace Math
    } // namespace Foundation

    #include <Foundation/Math/Complex/Complex.tpp>

#endif // FOUNDATION_MATH_COMPLEX_H