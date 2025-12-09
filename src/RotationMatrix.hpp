#pragma once
#include "Matrix.hpp"
#include <cmath>

class RotationMatrix : public Matrix {
public:
    RotationMatrix(double radians);
};

