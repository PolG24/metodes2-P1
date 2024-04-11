#include <stdio.h>
#include <stdbool.h>
#include "utils.c"

int main()
{
    double epsilon = 1.0 / 100000;
    int n = 30;
    int dim = n - 1; // We'll be working in dimension n - 1.

    // They get automatically initialized to all zeros.
    double prev_prev_x[dim], prev_x[dim], x[dim], b[dim], true_u[dim];

    // Initialize b using f. Initialize true_u (for comparison with the result obtained for each w).
    for (int i = 0; i < dim; i++)
    {
        b[i] = f(n, i + 1);
        true_u[i] = (i + 1) * sin(2 * PI * (i + 1) / n)/ n ;
    }

    // // Check b is well generated.
    // print_vec(dim, b);

    bool end = false;
    int iterations;
    int min_iterations = 10000;
    double best_w, spec_rad_approx;

    for (double w = 0.1; w < 1.99999; w += 0.0001)
    {
        // Reset the vectors to zero.
        for (int i = 0; i < dim; i++)
        {
            prev_prev_x[i] = 0;
            prev_x[i] = 0;
            x[i] = 0;
        }

        iterations = 0;
        end = false;
        while (!end)
        {
            // Save the prev_x array as the prev_prev_x array for the final spectral radius approximation.
            copyDoubleArray(prev_x, prev_prev_x, dim);
            // Save the x array as the previous array.
            copyDoubleArray(x, prev_x, dim);

            iterations++;
            // SOR iteration.
            x[0] = x[0] + w * (-x[0] + (b[0] + n * n * prev_x[1]) / (4 + 2 * n * n));
            for (int i = 1; i < dim - 1; i++)
            {
                x[i] = x[i] + w * (-x[i] + (b[i] + n * n * (x[i - 1] + prev_x[i + 1])) / (4 + 2 * n * n));
            }
            x[dim - 1] = x[dim - 1] + w * (-x[dim - 1] + (b[dim - 1] + n * n * x[dim - 2]) / (4 + 2 * n * n));

            // If the desired stopping condition is met, stop iterating.
            if (infinityDistance(x, prev_x, dim) < epsilon)
            {
                end = true;
            }
        }
        printf("For w = %e, %d iterations were made.\n", w, iterations);
        printf("Approximation of the spectral radius: %e.\n", approximate_spectral_radius(x, prev_x, prev_prev_x, dim));
        printf("Error: %e.\n\n", infinityDistance(true_u, x, dim));

        // If a new best w has been found, update it, the spectral radius and the minimum number of iterations.
        if (iterations < min_iterations)
        {
            best_w = w;
            min_iterations = iterations;
            spec_rad_approx = approximate_spectral_radius(x, prev_x, prev_prev_x, dim);
        }
    }

    printf("Number of iterations: %d.\n", min_iterations);
    printf("Best w: %e.\n", best_w);
    printf("Spectral radius approximation found with this w: %e.\n", spec_rad_approx);

    return 0;
}