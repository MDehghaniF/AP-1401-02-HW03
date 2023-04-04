#include "../include/matrix.h"

Matrix::Matrix()
    : Matrix(0)
{
}

Matrix::Matrix(int size)
    : Matrix(size, size)
{
}

Matrix::Matrix(int row, int column)
    : Matrix(row, column, 0.0)
{
}

Matrix::Matrix(int row, int column, double num)
{
    rowCapacity = 2;
    colCapacity = 2;
    rowSize = row;
    colSize = column;
    while (rowCapacity < rowSize) {
        rowCapacity *= 2;
    }
    while (colCapacity < colSize) {
        colCapacity *= 2;
    }
    data = new double*[rowCapacity];
    for (size_t i {}; i < rowCapacity; i++) {
        data[i] = new double[colCapacity];
    }
    for (size_t i {}; i < rowCapacity; i++) {
        for (size_t j {}; j < colCapacity; j++) {
            data[i][j] = num;
        }
    }
}

Matrix::Matrix(std::initializer_list<std::initializer_list<double>> a)
{
    rowSize = a.size();
    colSize = 0;
    for (auto& x : a)
        if (x.size() > colSize)
            colSize = x.size();
    rowCapacity = 2;
    colCapacity = 2;
    while (rowCapacity < rowSize) {
        rowCapacity *= 2;
    }
    while (colCapacity < colSize) {
        colCapacity *= 2;
    }
    data = new double*[rowCapacity];
    for (size_t i {}; i < rowCapacity; i++) {
        data[i] = new double[colCapacity];
        for (size_t j = 0; j < colCapacity; j++) {
            data[i][j] = 0.0;
        }
    }
    int i {};
    for (auto& x : a) {
        int j {};
        for (auto& y : x) {
            data[i][j] = y;
            j++;
        }
        i++;
    }
}

Matrix::Matrix(const Matrix& m)
{
    colSize = m.getColSize();
    rowSize = m.getRowSize();
    colCapacity = m.getColCapacity();
    rowCapacity = m.getRowCapacity();
    data = new double*[rowCapacity];
    for (size_t i {}; i < rowCapacity; i++) {
        data[i] = new double[colCapacity];
        for (size_t j {}; j < colCapacity; j++) {
            data[i][j] = 0.0;
        }
    }
    for (size_t i {}; i < rowSize; i++) {
        for (size_t j {}; j < colSize; j++) {
            data[i][j] = m[i][j];
        }
    }
}

Matrix::~Matrix()
{
    for (size_t i {}; i < rowCapacity; i++) {
        delete data[i];
    }
    delete data;
}

size_t Matrix::getRowSize() const
{
    return rowSize;
}

size_t Matrix::getColSize() const
{
    return colSize;
}

size_t Matrix::getRowCapacity() const
{
    return rowCapacity;
}

size_t Matrix::getColCapacity() const
{
    return colCapacity;
}

double** Matrix::getMatrix()
{
    return data;
}

const Matrix& Matrix::append(const Matrix& m, bool axis)
{
    if (axis == false) { // horizontally
        double** newData;
        while (colCapacity < (colSize + m.getColSize())) {
            colCapacity *= 2;
        }
        newData = new double*[rowCapacity];
        for (size_t i {}; i < rowCapacity; i++) {
            newData[i] = new double[colCapacity];
        }
        for (size_t i {}; i < rowSize; i++) {
            for (size_t j {}; j < colSize; j++) {
                newData[i][j] = data[i][j];
            }
            for (size_t j { colSize }; j < colSize + m.getColSize(); j++) {
                newData[i][j] = m[i][j - colSize];
            }
            delete data[i];
        }
        colSize += m.getColSize();
        delete data;
        data = newData;
        return *this;
    } else {
        double** newData;
        while (rowCapacity < (rowSize + m.getRowSize())) {
            rowCapacity *= 2;
        }
        newData = new double*[rowCapacity];
        for (size_t i {}; i < rowCapacity; i++) {
            newData[i] = new double[colCapacity];
        }
        for (size_t i {}; i < colSize; i++) {
            for (size_t j {}; j < rowSize; j++) {
                newData[j][i] = data[j][i];
            }
            for (size_t j { rowSize }; j < rowSize + m.getRowSize(); j++) {
                newData[j][i] = m[j - rowSize][i];
            }
        }
        for (size_t i {}; i < rowSize; i++) {
            delete data[i];
        }
        rowSize += m.getRowSize();
        delete data;

        data = newData;
        return *this;
    }
}

void Matrix::display() const
{
    std::cout << rowCapacity << " x " << colCapacity << " : " << rowSize << " x " << colSize << std::endl;
    for (size_t i {}; i < rowSize; i++) {
        for (size_t j {}; j < colSize; j++) {
            std::cout << data[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
Matrix Matrix::operator*(const Matrix& m)
{
    if (colSize == m.getRowSize()) {
        Matrix tmp(rowSize, m.getColSize());
        for (size_t i {}; i < rowSize; i++) {
            double sum {};
            for (size_t k {}; k < m.getColSize(); k++) {
                for (size_t j {}; j < colSize; j++) {
                    sum += data[i][j] * m[j][k];
                }
                tmp[i][k] = sum;
                sum = 0;
            }
        }
        return tmp;
    } else {
        throw std::out_of_range { "Can't Multiply" };
    }
}

Matrix Matrix::operator+(const Matrix& m)
{
    if (colSize == m.getColSize() && rowSize == m.getRowSize()) {
        Matrix tmp { *this };
        for (size_t i {}; i < rowSize; i++) {
            for (size_t j {}; j < colSize; j++) {
                tmp[i][j] = data[i][j] + m[i][j];
            }
        }
        return tmp;
    } else {
        throw std::out_of_range { "Can't Sum 1" };
    }
}

Matrix& Matrix::operator+=(const Matrix& m)
{
    if (colSize == m.getColSize() && rowSize == m.getRowSize()) {
        for (size_t i {}; i < rowSize; i++) {
            for (size_t j {}; j < colSize; j++) {
                data[i][j] += m[i][j];
            }
        }
        return *this;
    } else {
        throw std::out_of_range { "Can't Sum 2" };
    }
}

Matrix Matrix::operator-(const Matrix& m)
{
    if (colSize == m.getColSize() && rowSize == m.getRowSize()) {
        Matrix tmp { *this };
        for (size_t i {}; i < rowSize; i++) {
            for (size_t j {}; j < colSize; j++) {
                tmp[i][j] = data[i][j] - m[i][j];
            }
        }
        return tmp;
    } else {
        throw std::out_of_range { "Can't Subtract" };
    }
}

double Matrix::Determine()
{
    if (rowSize == colSize) {
        if (rowSize == 1) {
            return data[0][0];
        } else if (rowSize == 2) {
            return ((data[0][0] * data[1][1]) - (data[1][0] * data[0][1]));
        } else {
            double determine {};
            for (size_t n {}; n < colSize; n++) {
                Matrix tmp(rowSize - 1);
                for (size_t i { 1 }; i < rowSize; i++) {
                    size_t t {};
                    for (size_t j {}; j < colSize; j++) {
                        if (j == n) {
                            continue;
                        }
                        tmp[i - 1][t] = data[i][j];
                        t++;
                    }
                }
                if (n % 2 == 0) {
                    determine += tmp.Determine() * data[0][n];
                } else {
                    determine -= tmp.Determine() * data[0][n];
                }
            }
            return determine;
        }
    } else {
        throw std::out_of_range { "not Square" };
    }
}

Matrix Matrix::Transpose()
{
    Matrix tmp(colSize, rowSize);
    for (size_t i {}; i < rowSize; i++) {
        for (size_t j {}; j < colSize; j++) {
            tmp[j][i] = data[i][j];
        }
    }
    return tmp;
}

Matrix Matrix::Minor()
{
    Matrix tmp(rowSize, colSize);
    Matrix Dtmp(rowSize - 1, colSize - 1);
    for (size_t m {}; m < rowSize; m++) {
        for (size_t n {}; n < colSize; n++) {
            size_t k {};
            for (size_t i {}; i < rowSize; i++) {
                size_t t {};
                if (i == m) {
                    continue;
                }
                for (size_t j {}; j < colSize; j++) {
                    if (j == n) {
                        continue;
                    }
                    Dtmp[k][t] = data[i][j];
                    t++;
                }
                k++;
            }
            if ((m + n) % 2 == 0) {
                tmp[m][n] += Dtmp.Determine();
            } else {
                tmp[m][n] -= Dtmp.Determine();
            }
        }
    }
    return tmp;
}

Matrix Matrix::Reverse()
{
    Matrix tmp { *this };
    double d { this->Determine() };
    tmp = tmp.Minor().Transpose();
    for (size_t i {}; i < rowSize; i++) {
        for (size_t j {}; j < colSize; j++) {
            tmp[i][j] /= d;
        }
    }
    return tmp;
}

Matrix Matrix::operator|(const Matrix& m)
{
    Matrix tmp { *this };
    tmp = tmp.Reverse();
    tmp = tmp * m;
    return tmp;
}

Matrix& Matrix::operator++()
{
    return (*this += Matrix(rowSize, colSize, 1.0));
}

Matrix Matrix::operator++(int)
{
    Matrix tmp { *this };
    *this += Matrix(rowSize, colSize, 1.0);
    return tmp;
}

Matrix& Matrix::operator--()
{
    return (*this += Matrix(rowSize, colSize, -1.0));
}

Matrix Matrix::operator--(int)
{
    Matrix tmp { *this };
    *this += Matrix(rowSize, colSize, -1.0);
    return tmp;
}

double* Matrix::operator[](size_t i) const
{
    return data[i];
}

bool Matrix::operator==(const Matrix& m)
{
    if (rowSize != m.getRowSize())
        return false;
    else if (colSize != m.getColSize())
        return false;
    else {
        bool flag { true };
        for (size_t i = 0; i < rowSize; i++) {
            for (size_t j = 0; j < colSize; j++) {
                if (data[i][j] != m[i][j]) {
                    flag = false;
                }
            }
        }
        return flag;
    }
}
std::partial_ordering Matrix::operator<=>(const Matrix& m)
{
    if (rowSize != m.getRowSize()) {
        return rowSize <=> m.getRowSize();
    } else if (colSize != m.getColSize()) {
        return colSize <=> m.getColSize();
    } else {
        double sum1 {}, sum2 {};
        for (size_t i {}; i < rowSize; i++) {
            for (size_t j = 0; j < colSize; j++) {
                sum1 += data[i][j];
                sum2 += m[i][j];
            }
        }
        return sum1 <=> sum2;
    }
}

Matrix& Matrix::operator=(const Matrix& m)
{
    for (size_t i {}; i < rowCapacity; i++) {
        delete data[i];
    }
    delete data;
    colSize = m.getColSize();
    rowSize = m.getRowSize();
    colCapacity = m.getColCapacity();
    rowCapacity = m.getRowCapacity();
    data = new double*[rowCapacity];
    for (size_t i {}; i < rowCapacity; i++) {
        data[i] = new double[colCapacity];
        for (size_t j {}; j < colCapacity; j++) {
            data[i][j] = 0.0;
        }
    }
    for (size_t i {}; i < rowSize; i++) {
        for (size_t j {}; j < colSize; j++) {
            data[i][j] = m[i][j];
        }
    }
    return *this;
}
