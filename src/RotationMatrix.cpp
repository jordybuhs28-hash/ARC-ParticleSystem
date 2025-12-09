#include "RotationMatrix.hpp"
#include <cmath>

RotationMatrix::RotationMatrix(double radians)
    : Matrix(2, 2) {
    (*this)(0,0) = std::cos(radians);
    (*this)(0,1) = -std::sin(radians);
    (*this)(1,0) = std::sin(radians);
    (*this)(1,1) = std::cos(radians);
}
