#include <stdio.h>
#include <math.h>
#include <stdlib.h>


int main()
{
    double a, b, c;
    printf("Enter the lengths of three sides of a triangle:\n");

    scanf("%lf %lf %lf", &a, &b, &c);

    if (a <= 0 || b <= 0 || c <= 0)
    {
        perror("Error: All sides must be positive numbers.\n");
        exit(-1);
    }

    // Check if it's a Pythagorean triple
    if (a * a + b * b == c * c || a * a + c * c == b * b || b * b + c * c == a * a)
    {
        double alpha, beta, gamma;

        // Calculate angles in radians using trigonometric functions
        alpha = acos((b * b + c * c - a * a) / (2 * b * c));
        beta = acos((a * a + c * c - b * b) / (2 * a * c));
        gamma = acos((a * a + b * b - c * c) / (2 * a * b));

        printf("The triangle is a Pythagorean triple.\n");
        printf("Angles (in radians): alpha = %.2lf, beta = %.2lf, gamma = %.2lf\n", alpha, beta, gamma);
    }
    else
    {
        printf("Error: Not a Pythagorean triple.\n");
    }

    return 0;
}
