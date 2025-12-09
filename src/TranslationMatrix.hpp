#pragma once
#include "Matrix.hpp"

class TranslationMatrix : public Matrix {
public:
    TranslationMatrix(double dx, double dy, int cols);
};
