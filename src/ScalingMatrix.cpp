#include "ScalingMatrix.hpp"

ScalingMatrix::ScalingMatrix(double factor)
    : Matrix(2, 2) {
    (*this)(0,0) = factor;
    (*this)(1,1) = factor;
}
