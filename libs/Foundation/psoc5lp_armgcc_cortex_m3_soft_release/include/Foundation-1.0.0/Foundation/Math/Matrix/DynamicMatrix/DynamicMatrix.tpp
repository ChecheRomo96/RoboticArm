#ifndef FOUNDATION_MATH_DYNAMIC_MATRIX_TPP
#define FOUNDATION_MATH_DYNAMIC_MATRIX_TPP

#include <stdlib.h>
#include "DynamicMatrix.h"

namespace Foundation {
namespace Math {

template <typename T>
DynamicMatrix<T>::DynamicMatrix()
    : _data(0),
      _rows(0),
      _cols(0),
      _ownsData(false) {}

template <typename T>
DynamicMatrix<T>::DynamicMatrix(unsigned int rows, unsigned int cols)
    : _data(0),
      _rows(0),
      _cols(0),
      _ownsData(false) {
    Allocate(rows, cols);
    Zero();
}

template <typename T>
DynamicMatrix<T>::DynamicMatrix(
    unsigned int rows,
    unsigned int cols,
    T value
)
    : _data(0),
      _rows(0),
      _cols(0),
      _ownsData(false) {
    Allocate(rows, cols);
    Fill(value);
}

template <typename T>
DynamicMatrix<T>::DynamicMatrix(
    unsigned int rows,
    unsigned int cols,
    T* externalData
)
    : _data(0),
      _rows(0),
      _cols(0),
      _ownsData(false) {
    Attach(rows, cols, externalData);
}

template <typename T>
DynamicMatrix<T>::DynamicMatrix(const DynamicMatrix<T>& other)
    : _data(0),
      _rows(0),
      _cols(0),
      _ownsData(false) {
    Allocate(other._rows, other._cols);

    for(unsigned int i = 0; i < Size(); i++) {
        _data[i] = other._data[i];
    }
}

template <typename T>
DynamicMatrix<T>::DynamicMatrix(DynamicMatrix<T>&& other)
    : _data(other._data),
      _rows(other._rows),
      _cols(other._cols),
      _ownsData(other._ownsData) {
    other._data = 0;
    other._rows = 0;
    other._cols = 0;
    other._ownsData = false;
}

template <typename T>
DynamicMatrix<T>::~DynamicMatrix() {
    Release();
}

template <typename T>
DynamicMatrix<T>& DynamicMatrix<T>::operator=(
    const DynamicMatrix<T>& other
) {
    if(this == &other) {
        return *this;
    }

    Allocate(other._rows, other._cols);

    for(unsigned int i = 0; i < Size(); i++) {
        _data[i] = other._data[i];
    }

    return *this;
}

template <typename T>
DynamicMatrix<T>& DynamicMatrix<T>::operator=(
    DynamicMatrix<T>&& other
) {
    if(this == &other) {
        return *this;
    }

    Release();

    _data = other._data;
    _rows = other._rows;
    _cols = other._cols;
    _ownsData = other._ownsData;

    other._data = 0;
    other._rows = 0;
    other._cols = 0;
    other._ownsData = false;

    return *this;
}

template <typename T>
T* DynamicMatrix<T>::operator[](unsigned int row) {
    return &_data[row * _cols];
}

template <typename T>
const T* DynamicMatrix<T>::operator[](unsigned int row) const {
    return &_data[row * _cols];
}

template <typename T>
void DynamicMatrix<T>::Release() {
    if(_ownsData && _data != 0) {
        delete[] _data;
    }

    _data = 0;
    _rows = 0;
    _cols = 0;
    _ownsData = false;
}

template <typename T>
unsigned int DynamicMatrix<T>::Index(unsigned int row, unsigned int col) const {
    return (row * _cols) + col;
}

template <typename T>
bool DynamicMatrix<T>::Allocate(unsigned int rows, unsigned int cols) {
    if(rows == 0 || cols == 0) {
        Release();
        return false;
    }

    if(_ownsData && _data != 0 && _rows == rows && _cols == cols) {
        return true;
    }

    Release();

    _data = new T[rows * cols];

    if(_data == 0) {
        _rows = 0;
        _cols = 0;
        _ownsData = false;
        return false;
    }

    _rows = rows;
    _cols = cols;
    _ownsData = true;

    return true;
}

template <typename T>
void DynamicMatrix<T>::Attach(
    unsigned int rows,
    unsigned int cols,
    T* externalData
) {
    Release();

    _data = externalData;
    _rows = rows;
    _cols = cols;
    _ownsData = false;
}

template <typename T>
void DynamicMatrix<T>::Clear() {
    Release();
}

template <typename T>
unsigned int DynamicMatrix<T>::RowsCount() const {
    return _rows;
}

template <typename T>
unsigned int DynamicMatrix<T>::ColsCount() const {
    return _cols;
}

template <typename T>
unsigned int DynamicMatrix<T>::Size() const {
    return _rows * _cols;
}

template <typename T>
bool DynamicMatrix<T>::IsValid() const {
    return _data != 0 && _rows > 0 && _cols > 0;
}

template <typename T>
bool DynamicMatrix<T>::OwnsData() const {
    return _ownsData;
}

template <typename T>
T* DynamicMatrix<T>::Data() {
    return _data;
}

template <typename T>
const T* DynamicMatrix<T>::Data() const {
    return _data;
}

template <typename T>
T& DynamicMatrix<T>::At(unsigned int row, unsigned int col) {
    return _data[Index(row, col)];
}

template <typename T>
const T& DynamicMatrix<T>::At(unsigned int row, unsigned int col) const {
    return _data[Index(row, col)];
}

template <typename T>
DynamicMatrix<T> DynamicMatrix<T>::operator+(
    const DynamicMatrix<T>& other
) const {
    DynamicMatrix<T> result(_rows, _cols);

    if(_rows != other._rows || _cols != other._cols) {
        result.Clear();
        return result;
    }

    for(unsigned int i = 0; i < Size(); i++) {
        result._data[i] = _data[i] + other._data[i];
    }

    return result;
}

template <typename T>
DynamicMatrix<T> DynamicMatrix<T>::operator-(
    const DynamicMatrix<T>& other
) const {
    DynamicMatrix<T> result(_rows, _cols);

    if(_rows != other._rows || _cols != other._cols) {
        result.Clear();
        return result;
    }

    for(unsigned int i = 0; i < Size(); i++) {
        result._data[i] = _data[i] - other._data[i];
    }

    return result;
}

template <typename T>
DynamicMatrix<T>& DynamicMatrix<T>::operator+=(
    const DynamicMatrix<T>& other
) {
    if(_rows != other._rows || _cols != other._cols) {
        return *this;
    }

    for(unsigned int i = 0; i < Size(); i++) {
        _data[i] += other._data[i];
    }

    return *this;
}

template <typename T>
DynamicMatrix<T>& DynamicMatrix<T>::operator-=(
    const DynamicMatrix<T>& other
) {
    if(_rows != other._rows || _cols != other._cols) {
        return *this;
    }

    for(unsigned int i = 0; i < Size(); i++) {
        _data[i] -= other._data[i];
    }

    return *this;
}

template <typename T>
DynamicMatrix<T> DynamicMatrix<T>::operator*(T scalar) const {
    DynamicMatrix<T> result(_rows, _cols);

    for(unsigned int i = 0; i < Size(); i++) {
        result._data[i] = _data[i] * scalar;
    }

    return result;
}

template <typename T>
DynamicMatrix<T> DynamicMatrix<T>::operator/(T scalar) const {
    DynamicMatrix<T> result(_rows, _cols);

    for(unsigned int i = 0; i < Size(); i++) {
        result._data[i] = _data[i] / scalar;
    }

    return result;
}

template <typename T>
DynamicMatrix<T>& DynamicMatrix<T>::operator*=(T scalar) {
    for(unsigned int i = 0; i < Size(); i++) {
        _data[i] *= scalar;
    }

    return *this;
}

template <typename T>
DynamicMatrix<T>& DynamicMatrix<T>::operator/=(T scalar) {
    for(unsigned int i = 0; i < Size(); i++) {
        _data[i] /= scalar;
    }

    return *this;
}

template <typename T>
bool DynamicMatrix<T>::operator==(const DynamicMatrix<T>& other) const {
    if(_rows != other._rows || _cols != other._cols) {
        return false;
    }

    for(unsigned int i = 0; i < Size(); i++) {
        if(_data[i] != other._data[i]) {
            return false;
        }
    }

    return true;
}

template <typename T>
bool DynamicMatrix<T>::operator!=(const DynamicMatrix<T>& other) const {
    return !(*this == other);
}

template <typename T>
void DynamicMatrix<T>::Fill(T value) {
    for(unsigned int i = 0; i < Size(); i++) {
        _data[i] = value;
    }
}

template <typename T>
void DynamicMatrix<T>::Zero() {
    Fill(T());
}

template <typename T>
bool DynamicMatrix<T>::TransposeTo(DynamicMatrix<T>& result) const {
    if(!result.Allocate(_cols, _rows)) {
        return false;
    }

    for(unsigned int i = 0; i < _rows; i++) {
        for(unsigned int j = 0; j < _cols; j++) {
            result.At(j, i) = At(i, j);
        }
    }

    return true;
}

template <typename T>
DynamicMatrix<T> DynamicMatrix<T>::Transposed() const {
    DynamicMatrix<T> result(_cols, _rows);
    TransposeTo(result);
    return result;
}

template <typename T>
DynamicMatrix<T> operator*(T scalar, const DynamicMatrix<T>& matrix) {
    return matrix * scalar;
}

} // namespace Math
} // namespace Foundation

#endif
