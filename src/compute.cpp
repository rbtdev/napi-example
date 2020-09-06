#include "compute.h"

double compute(double count)
{
    double sum = 0.0;
    long int iterations = 0;
    for (double i = 1; i <= count; i++)
    {
        for (double j = 1; j <= count; j++)
        {
            iterations++;
            sum += i + j;
        }
    }
    return iterations;
}