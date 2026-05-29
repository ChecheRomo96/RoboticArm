#ifndef FOUNDATION_MATH_MATRIX_OPERATIONS_H
#define FOUNDATION_MATH_MATRIX_OPERATIONS_H

#include <Foundation/Math/Matrix/FixedMatrix/FixedMatrix.h>
#include <Foundation/Math/Matrix/DynamicMatrix/DynamicMatrix.h>

namespace Foundation {
namespace Math {

template <
    typename T,
    unsigned int RowsA,
    unsigned int ColsA,
    unsigned int ColsB
>
void Multiply(
    const FixedMatrix<T, RowsA, ColsA>& a,
    const FixedMatrix<T, ColsA, ColsB>& b,
    FixedMatrix<T, RowsA, ColsB>& result
) {
    for(unsigned int i = 0; i < RowsA; i++) {
        for(unsigned int j = 0; j < ColsB; j++) {
            result[i][j] = T();

            for(unsigned int k = 0; k < ColsA; k++) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

template <typename T>
bool Multiply(
    const DynamicMatrix<T>& a,
    const DynamicMatrix<T>& b,
    DynamicMatrix<T>& result
) {
    if(a.ColsCount() != b.RowsCount()) {
        return false;
    }

    if(!result.Allocate(a.RowsCount(), b.ColsCount())) {
        return false;
    }

    for(unsigned int i = 0; i < a.RowsCount(); i++) {
        for(unsigned int j = 0; j < b.ColsCount(); j++) {
            result.At(i, j) = T();

            for(unsigned int k = 0; k < a.ColsCount(); k++) {
                result.At(i, j) += a.At(i, k) * b.At(k, j);
            }
        }
    }

    return true;
}

template <
    typename T,
    unsigned int RowsA,
    unsigned int ColsA,
    unsigned int ColsB
>
bool Multiply(
    const FixedMatrix<T, RowsA, ColsA>& a,
    const DynamicMatrix<T>& b,
    DynamicMatrix<T>& result
) {
    if(b.RowsCount() != ColsA) {
        return false;
    }

    if(!result.Allocate(RowsA, b.ColsCount())) {
        return false;
    }

    for(unsigned int i = 0; i < RowsA; i++) {
        for(unsigned int j = 0; j < b.ColsCount(); j++) {
            result.At(i, j) = T();

            for(unsigned int k = 0; k < ColsA; k++) {
                result.At(i, j) += a[i][k] * b.At(k, j);
            }
        }
    }

    return true;
}

template <
    typename T,
    unsigned int RowsB,
    unsigned int ColsB
>
bool Multiply(
    const DynamicMatrix<T>& a,
    const FixedMatrix<T, RowsB, ColsB>& b,
    DynamicMatrix<T>& result
) {
    if(a.ColsCount() != RowsB) {
        return false;
    }

    if(!result.Allocate(a.RowsCount(), ColsB)) {
        return false;
    }

    for(unsigned int i = 0; i < a.RowsCount(); i++) {
        for(unsigned int j = 0; j < ColsB; j++) {
            result.At(i, j) = T();

            for(unsigned int k = 0; k < RowsB; k++) {
                result.At(i, j) += a.At(i, k) * b[k][j];
            }
        }
    }

    return true;
}

} // namespace Math
} // namespace Foundation

#endif
