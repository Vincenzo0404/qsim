#include "complex.h"

complex complex_vector_mul(complex *v1, complex *v2, unsigned long long int n) {
    complex c = {0.0, 0.0};
    for (unsigned long long int i = 0; i < n; i++) {
        c = complex_sum(c, complex_mul(v1[i], v2[i]));
    }
    return c;
}

complex complex_mul(complex c1, complex c2) {
    complex result;
    result.real = c1.real * c2.real - c1.imaginary * c2.imaginary;
    result.imaginary = c1.real * c2.imaginary + c1.imaginary * c2.real;
    return result;
}



complex complex_sum(complex c1, complex c2) {
    complex result;
    result.real = c1.real + c2.real;
    result.imaginary = c1.imaginary + c2.imaginary;
    return result;
}

void complex_print(complex c) {
    if (c.real == 0 && c.imaginary == 0) {
        printf("0");
        return;
    }

    if (c.real != 0) {
        printf("%.4g", c.real);
    }

    if (c.imaginary != 0) {
        if (c.imaginary > 0 && c.real != 0)
            printf("+");
        else if (c.imaginary < 0)
            printf("-");

        double abs_imag = c.imaginary < 0 ? -c.imaginary : c.imaginary;

        if (abs_imag == 1.0f)
            printf("i");
        else
            printf("i%.4g", abs_imag);
    }
}

