#pragma once
#include <vector>

class Matrix {
public:
    Matrix(int rows, int cols);

    double& operator()(int row, int col);
    const double& operator()(int row, int col) const;

    int getRows() const { return rows_; }
    int getCols() const { return cols_; }

    Matrix multiply(const Matrix& other) const;
    Matrix add(const Matrix& other) const;

    static Matrix identity(int n);     // extra credit
    Matrix transpose() const;          // extra credit

private:
    int rows_, cols_;
    std::vector<std::vector<double>> data_;
};
