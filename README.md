# Task7

# ABC computation with unit tests (C and Julia)

Here you find two implementations (in **C** and **Julia**) of a basic vector operation $$\vec{d}=a\cdot\vec{x}+\vec{y},$$ with $$\vec{x}$$, $$\vec{y}$$ and $$\vec{d}$$ N-dimensional vectors and $a$ a scalar. 
\
The codes for the sum are quite simple, especially the Julia one. Here, I assume you work using Docker with a container that includes both Julia and gcc.
\
The logic for the tests is the following: \
1. First check: if $x=0$, then $$\vec{d}=\vec{y}$$;
2. Second test: if $y=0$ then $\vec{d}=a\cdot\vec{x}$;
3. Last check: if $r1=a x+y$ and $$r2=a (2 x)+(2 y)$$, then $$r1=r2$$ (linearity).
These tests are performed considering some values for $a$, $x$ and $y$.

# Code in Julia
In Julia, I use the **Test** package to verify the linearity of the sum. The first part of the code defines the **vector_sum** function. The second part performs tests on **vector_sum**. Including this code in Julia, we can immediately see if any test fails. Then, we can use vector_sum by passing the arguments (a,x,y,N).

```
using Test

## Function that performs the vector sum: z = a * x + y
function vector_sum(a::Real, x::Real, y::Real, N::Integer)
    # in doing so, you can write any number (without points) as arguments of the function
    a = Float64(a)
    x = Float64(x)
    y = Float64(y)
    N = Int(N)
    xvec = fill(x, N)
    yvec = fill(y, N)
    return a .* xvec .+ yvec
end

## Unit tests
function run_tests()
    println("Running tests...")

    # Test 1: if y=0, result should be a*x
    @test vector_sum(2.0, 3.0, 0.0, 5) == fill(2.0 * 3.0, 5)

    # Test 2: if x=0, result should be y
    @test vector_sum(2.0, 0.0, 3.0, 5) == fill(3.0, 5)

    # Test 3: doubling x and y doubles the result
    r1 = vector_sum(1.5, 2.0, 3.0, 5)
    r2 = vector_sum(1.5, 4.0, 6.0, 5)
    @test r2 == 2 .* r1

    println("All tests passed.")
end

run_tests()
```


# Code in C
in C there is no built-in testing package. Here we follow the same strategy as before: build vectors $\vec{x}$ and $\vec{y}$, define the sum function **vectro_sum**, then test the linearity. The code show when tests fail. Finally, it perform vector sum with given imput values. 

```
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

bool arrays_equal_scaled(double* arr1, double* arr2, int N, double scale, double tol) {
    for (int i = 0; i < N; i++) {
        if (fabs(arr2[i] - scale * arr1[i]) > tol) {
            return false;
        }
    }
    return true;
}

// Vector sum function: d = a * x + y
void vector_sum(double a, double x, double y, int N, double* result) {
    for (int i = 0; i < N; i++) {
        result[i] = a * x + y;
    }
}

// Run tests to verify vector_sum correctness
void run_tests() {
    const int N = 5;
    const double tol = 1e-9;

    double r1[N];
    double r2[N];

    // Test 1: if y = 0, result should be a*x
    vector_sum(2.0, 3.0, 0.0, N, r1);
    for (int i = 0; i < N; i++) {
        if (fabs(r1[i] - 2.0 * 3.0) > tol) {
            printf("Test 1 failed!\n");
            exit(1);
        }
    }

    // Test 2: if x = 0, result should be y
    vector_sum(2.0, 0.0, 3.0, N, r1);
    for (int i = 0; i < N; i++) {
        if (fabs(r1[i] - 3.0) > tol) {
            printf("Test 2 failed!\n");
            exit(1);
        }
    }

    // Test 3: r2 should be 2 * r1
    vector_sum(1.5, 2.0, 3.0, N, r1);
    vector_sum(1.5, 4.0, 6.0, N, r2);
    if (!arrays_equal_scaled(r1, r2, N, 2.0, tol)) {
        printf("Test 3 failed!\n");
        exit(1);
    }

    printf("All tests passed.\n");
}

int main(int argc, char* argv[]) {
    if (argc != 5) {
        printf("Usage: %s a x y N\n", argv[0]);
        printf("Computes vector z = a * x + y with length N\n");
        return 1;
    }

    // Run tests first
    run_tests();

    double a = atof(argv[1]);
    double x = atof(argv[2]);
    double y = atof(argv[3]);
    int N = atoi(argv[4]);

    if (N <= 0) {
        printf("N must be positive.\n");
        return 1;
    }

    double* result = malloc(N * sizeof(double));
    if (!result) {
        printf("Memory allocation failed.\n");
        return 1;
    }
    
    // Vector sum

    vector_sum(a, x, y, N, result);

    int max_print = 10;
    int to_print = (N < max_print) ? N : max_print;

    // Print results

    printf("\nVector sum with N=%d, a=%.2f, x=%.2f, y=%.2f\n", N, a, x, y);
    printf("Result (showing max %d elements):\n", max_print);
    for (int i = 0; i < to_print; i++) {
        printf("z[%d] = %.2f\n", i, result[i]);
    }
    if (N > max_print) {
        printf("... (output truncated, total elements %d)\n", N);
    }

    free(result);
    return 0;
}
```

After saving this code, e.g., sum_testC.c, compile it 
 ```
gcc -o sum_test sum_testC.c -lm
```
and then run the code
```
./sum_test 2.0 3.0 4.0 1000
```
The arguments are a, x, y, N). As for Julia, the code first tests the functions, then it shows the result of the sum.

