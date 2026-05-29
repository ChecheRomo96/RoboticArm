#ifndef FOUNDATION_MATH_DYNAMIC_MATRIX_H
#define FOUNDATION_MATH_DYNAMIC_MATRIX_H

namespace Foundation {
namespace Math {

template <typename T>
class DynamicMatrix {
private:

    T* _data;
    unsigned int _rows;
    unsigned int _cols;
    bool _ownsData;

    void Release();
    unsigned int Index(unsigned int row, unsigned int col) const;

public:

    DynamicMatrix();
    DynamicMatrix(unsigned int rows, unsigned int cols);
    DynamicMatrix(unsigned int rows, unsigned int cols, T value);
    DynamicMatrix(unsigned int rows, unsigned int cols, T* externalData);
    DynamicMatrix(const DynamicMatrix<T>& other);
    DynamicMatrix(DynamicMatrix<T>&& other);

    ~DynamicMatrix();

    DynamicMatrix<T>& operator=(const DynamicMatrix<T>& other);
    DynamicMatrix<T>& operator=(DynamicMatrix<T>&& other);

    bool Allocate(unsigned int rows, unsigned int cols);
    void Attach(unsigned int rows, unsigned int cols, T* externalData);
    void Clear();

    unsigned int RowsCount() const;
    unsigned int ColsCount() const;
    unsigned int Size() const;
    bool IsValid() const;
    bool OwnsData() const;

    T* Data();
    const T* Data() const;

    T& At(unsigned int row, unsigned int col);
    const T& At(unsigned int row, unsigned int col) const;

    DynamicMatrix<T> operator+(const DynamicMatrix<T>& other) const;
    DynamicMatrix<T> operator-(const DynamicMatrix<T>& other) const;

    DynamicMatrix<T>& operator+=(const DynamicMatrix<T>& other);
    DynamicMatrix<T>& operator-=(const DynamicMatrix<T>& other);

    DynamicMatrix<T> operator*(T scalar) const;
    DynamicMatrix<T> operator/(T scalar) const;

    DynamicMatrix<T>& operator*=(T scalar);
    DynamicMatrix<T>& operator/=(T scalar);

    bool operator==(const DynamicMatrix<T>& other) const;
    bool operator!=(const DynamicMatrix<T>& other) const;

    T* operator[](unsigned int row);
    const T* operator[](unsigned int row) const;

    void Fill(T value);
    void Zero();

    bool TransposeTo(DynamicMatrix<T>& result) const;
    DynamicMatrix<T> Transposed() const;
};

template <typename T>
DynamicMatrix<T> operator*(T scalar, const DynamicMatrix<T>& matrix);

} // namespace Math
} // namespace Foundation

#include <Foundation/Math/Matrix/DynamicMatrix/DynamicMatrix.tpp>

#endif
