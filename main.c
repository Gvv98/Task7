#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "vector_sum.h"


// My tests
void run_tests() {
    double result[100];

    // Test 1: if a=2 and x=1, then d=2
    vector_sum(2, 3, 0.0, 100, result);  
    for (int i = 0; i < 100; i++) {
        if (fabs(result[i] - 6.0) > 1e-6) {
            printf("Test 1 failed!\n");
            exit(1);
        }
    }

    // Test 2: if a=y=x=1, then d=2
    vector_sum(2.0, 0, 1, 100, result);  
    for (int i = 0; i < 100; i++) {
        if (fabs(result[i] - 1.0) > 1e-6) {
            printf("Test 2 failed!\n");
            exit(1);
        }
    }

    // Test 3: if a=0, then d=y
    double result1[100], result2[100];
    vector_sum(2, 1.0, 1.0, 100, result1);  
    vector_sum(2, 2.0, 2.0, 100, result2);  
    for (int i = 0; i < 100; i++) {
        if (fabs(2*result1[i] - result2[i]) > 1e-6) {
            printf("Test 3 failed!\n");
            exit(1);
        }
    }

    printf("All tests passed.\n");
}

int main(int argc, char* argv[]) {
    // Run unit tests first
    run_tests();

    if (argc != 5) {
        printf("Usage: %s a x y N\n", argv[0]);
        printf("Computes vector z = a * x + y with length N\n");
        return 1;
    }

    double a = atof(argv[1]);
    double x = atof(argv[2]);
    double y = atof(argv[3]);
    int N = atoi(argv[4]);
    // N>0
    if (N <= 0) {
        printf("N must be positive.\n");
        return 1;
    }

    double* result = malloc(N * sizeof(double));
    if (!result) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    vector_sum(a, x, y, N, result);

    int max_print = 10;
    int to_print = (N < max_print) ? N : max_print;

    printf("\nVector sum with N=%d, a=%.2f, x=%.2f, y=%.2f\n", N, a, x, y);
    printf("Result (showing max %d elements):\n", max_print);
    for (int i = 0; i < to_print; i++) {
        printf("d[%d] = %.2f\n", i, result[i]);
    }
    if (N > max_print) {
        printf("...\n", N);
    }

    free(result);
    return 0;
}
