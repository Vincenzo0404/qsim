#include "complex.h"

/* computes row × column product */
complex complex_vector_mul(complex *v1, complex *v2, unsigned int n) {
    complex c = {0.0, 0.0};
    for (int i = 0; i < n; i++) {
        c = complex_sum(c, complex_mul(v1[i], v2[i]));
    }
    return c;
}

/* multiplies two complex numbers */
complex complex_mul(complex c1, complex c2) {

    complex result;
    result.real = c1.real * c2.real - c1.imaginary * c2.imaginary;
    result.imaginary = c1.real * c2.imaginary + c1.imaginary * c2.real;
    return result;
}


/* sums two complex numbers */
complex complex_sum(complex c1, complex c2) {
    complex result;
    result.real = c1.real + c2.real;
    result.imaginary = c1.imaginary + c2.imaginary;
    return result;
}
void complex_print(complex c) {
    if (c.real != 0 || c.imaginary != 0) {
        if (c.real != 0) {
            printf("%.4g", c.real);
        }

        if (c.imaginary != 0) {
            if (c.imaginary > 0 && c.real != 0)
                printf("+");
            else {
                printf("-");
            }
            printf("%.4gi", c.imaginary < 0 ? -c.imaginary : c.imaginary);
        }
    } else {
        printf("0");
    }

    printf("\n");
}

