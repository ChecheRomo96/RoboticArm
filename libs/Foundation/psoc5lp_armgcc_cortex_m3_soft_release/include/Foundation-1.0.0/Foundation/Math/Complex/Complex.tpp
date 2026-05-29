#ifndef FOUNDATION_MATH_COMPLEX_TPP
#define FOUNDATION_MATH_COMPLEX_TPP

    #include "Complex.h"

    namespace Foundation {
    namespace Math {

        template <typename T>
        Complex<T>::Complex()
            : real(0),
            imag(0) {}

        template <typename T>
        Complex<T>::Complex(T real)
            : real(real),
            imag(0) {}

        template <typename T>
        Complex<T>::Complex(
            T real,
            T imag
        )
            : real(real),
            imag(imag) {}

        template <typename T>
        Complex<T>::Complex(
            const Complex<T>& other
        )
            : real(other.real),
            imag(other.imag) {}

        template <typename T>
        Complex<T>& Complex<T>::operator=(
            const Complex<T>& other
        ) {
            real = other.real;
            imag = other.imag;

            return *this;
        }

        template <typename T>
        Complex<T> Complex<T>::operator+() const {
            return *this;
        }

        template <typename T>
        Complex<T> Complex<T>::operator-() const {
            return Complex<T>(
                -real,
                -imag
            );
        }

        template <typename T>
        Complex<T> Complex<T>::operator+(
            const Complex<T>& other
        ) const {
            return Complex<T>(
                real + other.real,
                imag + other.imag
            );
        }

        template <typename T>
        Complex<T> Complex<T>::operator-(
            const Complex<T>& other
        ) const {
            return Complex<T>(
                real - other.real,
                imag - other.imag
            );
        }

        template <typename T>
        Complex<T> Complex<T>::operator*(
            const Complex<T>& other
        ) const {
            return Complex<T>(
                (real * other.real) - (imag * other.imag),
                (real * other.imag) + (imag * other.real)
            );
        }

        template <typename T>
        Complex<T> Complex<T>::operator/(
            const Complex<T>& other
        ) const {

            T den =
                (other.real * other.real) +
                (other.imag * other.imag);

            return Complex<T>(
                (
                    (real * other.real) +
                    (imag * other.imag)
                ) / den,

                (
                    (imag * other.real) -
                    (real * other.imag)
                ) / den
            );
        }

        template <typename T>
        Complex<T>& Complex<T>::operator+=(
            const Complex<T>& other
        ) {
            real += other.real;
            imag += other.imag;

            return *this;
        }

        template <typename T>
        Complex<T>& Complex<T>::operator-=(
            const Complex<T>& other
        ) {
            real -= other.real;
            imag -= other.imag;

            return *this;
        }

        template <typename T>
        Complex<T>& Complex<T>::operator*=(
            const Complex<T>& other
        ) {

            T r =
                (real * other.real) -
                (imag * other.imag);

            T i =
                (real * other.imag) +
                (imag * other.real);

            real = r;
            imag = i;

            return *this;
        }

        template <typename T>
        Complex<T>& Complex<T>::operator/=(
            const Complex<T>& other
        ) {

            T den =
                (other.real * other.real) +
                (other.imag * other.imag);

            T r =
                (
                    (real * other.real) +
                    (imag * other.imag)
                ) / den;

            T i =
                (
                    (imag * other.real) -
                    (real * other.imag)
                ) / den;

            real = r;
            imag = i;

            return *this;
        }

        template <typename T>
        bool Complex<T>::operator==(
            const Complex<T>& other
        ) const {
            return
                real == other.real &&
                imag == other.imag;
        }

        template <typename T>
        bool Complex<T>::operator!=(
            const Complex<T>& other
        ) const {
            return !(*this == other);
        }

        template <typename T>
        Complex<T> Complex<T>::Conjugate() const {
            return Complex<T>(
                real,
                -imag
            );
        }

        template <typename T>
        T Complex<T>::MagnitudeSquared() const {
            return
                (real * real) +
                (imag * imag);
        }

    } // namespace Math
    } // namespace Foundation

#endif//FOUNDATION_MATH_COMPLEX_TPP