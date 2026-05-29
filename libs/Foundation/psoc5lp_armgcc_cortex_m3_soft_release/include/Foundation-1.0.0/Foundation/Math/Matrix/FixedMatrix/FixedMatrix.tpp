#ifndef FOUNDATION_MATH_FIXED_MATRIX_TPP
#define FOUNDATION_MATH_FIXED_MATRIX_TPP

namespace Foundation {
namespace Math {

template <typename T, unsigned int Rows, unsigned int Cols>
FixedMatrix<T, Rows, Cols>::FixedMatrix() {
    Zero();
}

template <typename T, unsigned int Rows, unsigned int Cols>
FixedMatrix<T, Rows, Cols>::FixedMatrix(T value) {
    Fill(value);
}

template <typename T, unsigned int Rows, unsigned int Cols>
FixedMatrix<T, Rows, Cols>::FixedMatrix(
    const T (&values)[Rows][Cols]
) {
    for(unsigned int i = 0; i < Rows; i++) {
        for(unsigned int j = 0; j < Cols; j++) {
            _data[i][j] = values[i][j];
        }
    }
}

template <typename T, unsigned int Rows, unsigned int Cols>
FixedMatrix<T, Rows, Cols>::FixedMatrix(
    const FixedMatrix<T, Rows, Cols>& other
) {
    *this = other;
}

template <typename T, unsigned int Rows, unsigned int Cols>
FixedMatrix<T, Rows, Cols>& FixedMatrix<T, Rows, Cols>::operator=(
    const FixedMatrix<T, Rows, Cols>& other
) {
    if(this == &other) {
        return *this;
    }

    for(unsigned int i = 0; i < Rows; i++) {
        for(unsigned int j = 0; j < Cols; j++) {
            _data[i][j] = other._data[i][j];
        }
    }

    return *this;
}

template <typename T, unsigned int Rows, unsigned int Cols>
unsigned int FixedMatrix<T, Rows, Cols>::RowsCount() const {
    return Rows;
}

template <typename T, unsigned int Rows, unsigned int Cols>
unsigned int FixedMatrix<T, Rows, Cols>::ColsCount() const {
    return Cols;
}

template <typename T, unsigned int Rows, unsigned int Cols>
T* FixedMatrix<T, Rows, Cols>::Data() {
    return &_data[0][0];
}

template <typename T, unsigned int Rows, unsigned int Cols>
const T* FixedMatrix<T, Rows, Cols>::Data() const {
    return &_data[0][0];
}

template <typename T, unsigned int Rows, unsigned int Cols>
T& FixedMatrix<T, Rows, Cols>::At(
    unsigned int row,
    unsigned int col
) {
    return _data[row][col];
}

template <typename T, unsigned int Rows, unsigned int Cols>
const T& FixedMatrix<T, Rows, Cols>::At(
    unsigned int row,
    unsigned int col
) const {
    return _data[row][col];
}

template <typename T, unsigned int Rows, unsigned int Cols>
T* FixedMatrix<T, Rows, Cols>::operator[](unsigned int row) {
    return _data[row];
}

template <typename T, unsigned int Rows, unsigned int Cols>
const T* FixedMatrix<T, Rows, Cols>::operator[](unsigned int row) const {
    return _data[row];
}

template <typename T, unsigned int Rows, unsigned int Cols>
FixedMatrix<T, Rows, Cols> FixedMatrix<T, Rows, Cols>::operator+(
    const FixedMatrix<T, Rows, Cols>& other
) const {
    FixedMatrix<T, Rows, Cols> result;

    for(unsigned int i = 0; i < Rows; i++) {
        for(unsigned int j = 0; j < Cols; j++) {
            result._data[i][j] = _data[i][j] + other._data[i][j];
        }
    }

    return result;
}

template <typename T, unsigned int Rows, unsigned int Cols>
FixedMatrix<T, Rows, Cols> FixedMatrix<T, Rows, Cols>::operator-(
    const FixedMatrix<T, Rows, Cols>& other
) const {
    FixedMatrix<T, Rows, Cols> result;

    for(unsigned int i = 0; i < Rows; i++) {
        for(unsigned int j = 0; j < Cols; j++) {
            result._data[i][j] = _data[i][j] - other._data[i][j];
        }
    }

    return result;
}

template <typename T, unsigned int Rows, unsigned int Cols>
FixedMatrix<T, Rows, Cols>& FixedMatrix<T, Rows, Cols>::operator+=(
    const FixedMatrix<T, Rows, Cols>& other
) {
    for(unsigned int i = 0; i < Rows; i++) {
        for(unsigned int j = 0; j < Cols; j++) {
            _data[i][j] += other._data[i][j];
        }
    }

    return *this;
}

template <typename T, unsigned int Rows, unsigned int Cols>
FixedMatrix<T, Rows, Cols>& FixedMatrix<T, Rows, Cols>::operator-=(
    const FixedMatrix<T, Rows, Cols>& other
) {
    for(unsigned int i = 0; i < Rows; i++) {
        for(unsigned int j = 0; j < Cols; j++) {
            _data[i][j] -= other._data[i][j];
        }
    }

    return *this;
}

template <typename T, unsigned int Rows, unsigned int Cols>
FixedMatrix<T, Rows, Cols> FixedMatrix<T, Rows, Cols>::operator*(
    T scalar
) const {
    FixedMatrix<T, Rows, Cols> result;

    for(unsigned int i = 0; i < Rows; i++) {
        for(unsigned int j = 0; j < Cols; j++) {
            result._data[i][j] = _data[i][j] * scalar;
        }
    }

    return result;
}

template <typename T, unsigned int Rows, unsigned int Cols>
FixedMatrix<T, Rows, Cols> FixedMatrix<T, Rows, Cols>::operator/(
    T scalar
) const {
    FixedMatrix<T, Rows, Cols> result;

    for(unsigned int i = 0; i < Rows; i++) {
        for(unsigned int j = 0; j < Cols; j++) {
            result._data[i][j] = _data[i][j] / scalar;
        }
    }

    return result;
}

template <typename T, unsigned int Rows, unsigned int Cols>
FixedMatrix<T, Rows, Cols>& FixedMatrix<T, Rows, Cols>::operator*=(
    T scalar
) {
    for(unsigned int i = 0; i < Rows; i++) {
        for(unsigned int j = 0; j < Cols; j++) {
            _data[i][j] *= scalar;
        }
    }

    return *this;
}

template <typename T, unsigned int Rows, unsigned int Cols>
FixedMatrix<T, Rows, Cols>& FixedMatrix<T, Rows, Cols>::operator/=(
    T scalar
) {
    for(unsigned int i = 0; i < Rows; i++) {
        for(unsigned int j = 0; j < Cols; j++) {
            _data[i][j] /= scalar;
        }
    }

    return *this;
}

template <typename T, unsigned int Rows, unsigned int Cols>
bool FixedMatrix<T, Rows, Cols>::operator==(
    const FixedMatrix<T, Rows, Cols>& other
) const {
    for(unsigned int i = 0; i < Rows; i++) {
        for(unsigned int j = 0; j < Cols; j++) {
            if(_data[i][j] != other._data[i][j]) {
                return false;
            }
        }
    }

    return true;
}

template <typename T, unsigned int Rows, unsigned int Cols>
bool FixedMatrix<T, Rows, Cols>::operator!=(
    const FixedMatrix<T, Rows, Cols>& other
) const {
    return !(*this == other);
}

template <typename T, unsigned int Rows, unsigned int Cols>
void FixedMatrix<T, Rows, Cols>::Fill(T value) {
    for(unsigned int i = 0; i < Rows; i++) {
        for(unsigned int j = 0; j < Cols; j++) {
            _data[i][j] = value;
        }
    }
}

template <typename T, unsigned int Rows, unsigned int Cols>
void FixedMatrix<T, Rows, Cols>::Zero() {
    Fill(T());
}

template <typename T, unsigned int Rows, unsigned int Cols>
FixedMatrix<T, Cols, Rows> FixedMatrix<T, Rows, Cols>::Transposed() const {
    FixedMatrix<T, Cols, Rows> result;

    for(unsigned int i = 0; i < Rows; i++) {
        for(unsigned int j = 0; j < Cols; j++) {
            result[j][i] = _data[i][j];
        }
    }

    return result;
}

template <typename T, unsigned int Rows, unsigned int Cols>
FixedMatrix<T, Rows, Cols> FixedMatrix<T, Rows, Cols>::Filled(T value) {
    return FixedMatrix<T, Rows, Cols>(value);
}

template <typename T, unsigned int Rows, unsigned int Cols>
FixedMatrix<T, Rows, Cols> FixedMatrix<T, Rows, Cols>::Zeros() {
    return FixedMatrix<T, Rows, Cols>();
}

template <typename T, unsigned int Rows, unsigned int Cols>
FixedMatrix<T, Rows, Cols> operator*(
    T scalar,
    const FixedMatrix<T, Rows, Cols>& matrix
) {
    return matrix * scalar;
}

} // namespace Math
} // namespace Foundation

#endif
