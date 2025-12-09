#include "TranslationMatrix.hpp"

TranslationMatrix::TranslationMatrix(double dx, double dy, int cols)
    : Matrix(2, cols) {
    for (int j = 0; j < cols; j++) {
        (*this)(0,j) = dx;
        (*this)(1,j) = dy;
    }
}
