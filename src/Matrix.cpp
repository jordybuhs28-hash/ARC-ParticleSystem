#include "Matrix.hpp"
#include <stdexcept>

// Constructor: initializes rows x cols matrix with zeros
Matrix::Matrix(int rows, int cols)
    : rows_(rows), cols_(cols), data_(rows, std::vector<double>(cols, 0.0)) {}

// Element access (non-const)
double& Matrix::operator()(int row, int col) {
    if (row < 0 || row >= rows_ || col < 0 || col >= cols_)
        throw std::out_of_range("Matrix index out of range");
    return data_[row][col];
}

// Element access (const)
const double& Matrix::operator()(int row, int col) const {
    if (row < 0 || row >= rows_ || col < 0 || col >= cols_)
        throw std::out_of_range("Matrix index out of range");
    return data_[row][col];
}

// Multiply two matrices
Matrix Matrix::multiply(const Matrix& other) const {
    if (cols_ != other.rows_)
        throw std::invalid_argument("Matrix dimension mismatch for multiply");

    Matrix result(rows_, other.cols_);
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < other.cols_; j++) {
            double sum = 0.0;
            for (int k = 0; k < cols_; k++) {
                sum += data_[i][k] * other(k, j);
            }
            result(i, j) = sum;
        }
    }
    return result;
}

// Add two matrices
Matrix Matrix::add(const Matrix& other) const {
    if (rows_ != other.rows_ || cols_ != other.cols_)
        throw std::invalid_argument("Matrix dimension mismatch for add");

    Matrix result(rows_, cols_);
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            result(i, j) = data_[i][j] + other(i, j);
        }
    }
    return result;
}

// Identity matrix (extra credit)
Matrix Matrix::identity(int n) {
    Matrix I(n, n);
    for (int i = 0; i < n; i++) {
        I(i, i) = 1.0;
    }
    return I;
}

// Transpose (extra credit)
Matrix Matrix::transpose() const {
    Matrix T(cols_, rows_);
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            T(j, i) = data_[i][j];
        }
    }
    return T;
}
