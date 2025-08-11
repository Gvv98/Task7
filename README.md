# Task7

# ABC computation with unit tests (C and Julia)

Here you find two implementations (in **C** and **Julia**) of a basic vector operation $$\vec{d}=a\cdot\vec{x}+\vec{y},$$ with $$\vec{x}$$, $$\vec{y}$$ and $$\vec{d}$$ N-dimensional vectors and $a$ a scalar. 
\
The codes for the sum are quite simple, especially the Julia one. Here, I assume you work using Docker with a container that includes both Julia and gcc.
\
The logic for the tests is the following: \
1. First check: if $x=0$, then $$\vec{d}=\vec{y}$$;
2. Second test: if $y=0$ then $\vec{d}=a\cdot\vec{x}$;
3. Last check: if $r1=a x+y$ and $$r2=a (2 x)+(2 y)$$, then $$2 r1=r2$$ (linearity).
These tests are performed considering some values for $a$, $x$ and $y$.

# Code in Julia
In Julia, we use the **Test** package to verify the linearity of the sum. In [vectorsum_test.jl](https://github.com/Gvv98/Task7/blob/main/vectorsum_test.jl) you can find the **vector_sum** function. The test is implementend in **run_test** contained in **main.jl**. We can run the code by passing ``julia main.jl  a x y N``.


# Code in C
In C there is no built-in testing package. Here we follow the same strategy as before: define the sum function [vector_sum.c](https://github.com/Gvv98/Task7/blob/main/vector_sum.c), then test the linearity within [main.c](https://github.com/Gvv98/Task7/blob/main/main.c). Compile the codes with  ``gcc -o mainsum main.c vector_sum.c -lm``, then run it with ``./ mainsum a x y N``. The code immediately tells you if ``vector_sum.c`` passes all the tests and performs the sum with the values provided as input.

