#ifndef FOUNDATION_MATH_FIXED_MATRIX_H
#define FOUNDATION_MATH_FIXED_MATRIX_H

namespace Foundation {
namespace Math {

template <typename T, unsigned int Rows, unsigned int Cols>
class FixedMatrix {
private:

    T _data[Rows][Cols];

public:

    FixedMatrix();
    FixedMatrix(T value);
    FixedMatrix(const T (&values)[Rows][Cols]);
    FixedMatrix(const FixedMatrix<T, Rows, Cols>& other);

    FixedMatrix<T, Rows, Cols>& operator=(
        const FixedMatrix<T, Rows, Cols>& other
    );

    unsigned int RowsCount() const;
    unsigned int ColsCount() const;

    T* Data();
    const T* Data() const;

    T& At(unsigned int row, unsigned int col);
    const T& At(unsigned int row, unsigned int col) const;

    T* operator[](unsigned int row);
    const T* operator[](unsigned int row) const;

    FixedMatrix<T, Rows, Cols> operator+(
        const FixedMatrix<T, Rows, Cols>& other
    ) const;

    FixedMatrix<T, Rows, Cols> operator-(
        const FixedMatrix<T, Rows, Cols>& other
    ) const;

    FixedMatrix<T, Rows, Cols>& operator+=(
        const FixedMatrix<T, Rows, Cols>& other
    );

    FixedMatrix<T, Rows, Cols>& operator-=(
        const FixedMatrix<T, Rows, Cols>& other
    );

    FixedMatrix<T, Rows, Cols> operator*(T scalar) const;
    FixedMatrix<T, Rows, Cols> operator/(T scalar) const;

    FixedMatrix<T, Rows, Cols>& operator*=(T scalar);
    FixedMatrix<T, Rows, Cols>& operator/=(T scalar);

    bool operator==(
        const FixedMatrix<T, Rows, Cols>& other
    ) const;

    bool operator!=(
        const FixedMatrix<T, Rows, Cols>& other
    ) const;

    void Fill(T value);
    void Zero();

    FixedMatrix<T, Cols, Rows> Transposed() const;

    static FixedMatrix<T, Rows, Cols> Filled(T value);
    static FixedMatrix<T, Rows, Cols> Zeros();
};

template <typename T, unsigned int Rows, unsigned int Cols>
FixedMatrix<T, Rows, Cols> operator*(
    T scalar,
    const FixedMatrix<T, Rows, Cols>& matrix
);

} // namespace Math
} // namespace Foundation

#include <Foundation/Math/Matrix/FixedMatrix/FixedMatrix.tpp>

#endif
