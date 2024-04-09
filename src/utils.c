#include <math.h>
#define PI 3.14159265358979323846

double f(int n, int i)
{
    return (4 * i * (PI * PI + 1) * sin(2 * PI * i / n) / n) - (4 * PI * cos(2 * PI * i / n));
}

void print_vec(int dim, double vec[])
{
    for (int i = 0; i < dim; i++)
    {
        printf("%.5lf", vec[i]);
        if (i < dim - 1)
        {
            printf(", "); // Add a comma and space after each element except the last one
        }
    }
}

// Function to copy an array of doubles
void copyDoubleArray(double source[], double destination[], int size)
{
    for (int i = 0; i < size; i++)
    {
        destination[i] = source[i];
    }
}

// Function to calculate the infinity distance between two arrays of doubles
double infinityDistance(double arr1[], double arr2[], int size)
{
    double maxDiff = 0.0;

    for (int i = 0; i < size; i++)
    {
        double diff = fabs(arr1[i] - arr2[i]); // Absolute difference between corresponding elements
        if (diff > maxDiff)
        {
            maxDiff = diff; // Update maxDiff if the current difference is greater
        }
    }

    return maxDiff;
}