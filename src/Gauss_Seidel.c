#include <stdio.h>
#include <stdbool.h>
#include "utils.c"

int main()
{
    double epsilon = 1.0 / 100000; 
    int n = 30;
    int dim = n - 1; // We'll be working in dimension n - 1.

    // They get automatically initialized to all zeros.
    double prev_x[dim], x[dim], b[dim];

    // Initialize b using f
    for (int i = 0; i < dim; i++)
    {
        b[i] = f(n, i + 1);
    }

    // // Check b is well generated
    // print_vec(dim, b);

    bool end = false;
    int iterations = 0;

    while (!end)
    {
        iterations++;
        // Jacobi iteration
        x[0] = (b[0] + n * n * prev_x[1]) / (4 + 2 * n * n);
        for (int i = 1; i < dim - 1; i++)
        {
            x[i] = (b[i] + n * n * (x[i - 1] + prev_x[i + 1])) / (4 + 2 * n * n);
        }
        x[dim - 1] = (b[dim - 1] + n * n * x[dim - 2]) / (4 + 2 * n * n);

        // If the desired stopping condition is met, stop iterating.
        printf("%.20lf\n", infinityDistance(x, prev_x, dim));
        if (infinityDistance(x, prev_x, dim) < epsilon)
        {
            end = true;
        }

        // Save the x array as the previous array for the next iteration
        copyDoubleArray(x, prev_x, dim);
    }

    printf("Number of iterations: %d\n", iterations);

    return 0;
}