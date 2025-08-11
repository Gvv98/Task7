#include "vector_sum.h"

// Vector sum function: d = a * x + y
void vector_sum(double a, double x, double y, int N, double* result) {
    for (int i = 0; i < N; i++) {
        result[i] = a * x + y;
    }
}

