#ifndef MATRIX_H
#define MATRIX_H

#include <compare>
#include <initializer_list>
#include <iostream>
#include <utility>

class Matrix {
private:
    size_t colCapacity {};
    size_t rowCapacity {};
    size_t colSize {};
    size_t rowSize {};
    double** data;

public:
    Matrix();
    Matrix(int size);
    Matrix(int row, int column);
    Matrix(int row, int column, double num);
    Matrix(std::initializer_list<std::initializer_list<double>> a);
    Matrix(const Matrix& m);

    size_t getRowSize() const;
    size_t getColSize() const;
    size_t getRowCapacity() const;
    size_t getColCapacity() const;
    double** getMatrix();

    const Matrix& append(const Matrix& m, bool axis = false);
    void display() const;

    Matrix operator*(const Matrix&);
    Matrix operator+(const Matrix&);
    Matrix& operator+=(const Matrix&);
    Matrix operator-(const Matrix&);

    double Determine();
    Matrix Reverse();
    Matrix Transpose();
    Matrix Minor(); // Kehad

    Matrix operator|(const Matrix&);
    Matrix& operator++();
    Matrix operator++(int);
    Matrix& operator--();
    Matrix operator--(int);
    double* operator[](size_t i) const;
    bool operator==(const Matrix&);
    std::partial_ordering operator<=>(const Matrix&);
    Matrix& operator=(const Matrix&);
    friend std::ostream& operator<<(std::ostream& os, const Matrix& m)
    {
        m.display();
        return os;
    }

    ~Matrix();
};
#endif // !MATRIX_H