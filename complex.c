#include "complex.h"

complex complex_vector_mul(complex *v1, complex *v2, unsigned int n) {
    /* computes row * column product */
    complex c = {0.0, 0.0};
    for (int i = 0; i < n; i++) {
        c = complex_sum(c, complex_mul(v1[i], v2[i]));
    }
    return c;
}

complex complex_mul(complex c1, complex c2) {
    /* multiplies two complex numbers */
    complex result;
    result.real = c1.real * c2.real - c1.imaginary * c2.imaginary;
    result.imaginary = c1.real * c2.imaginary + c1.imaginary * c2.real;
    return result;
}


complex complex_sum(complex c1, complex c2) {
    /* sums two complex numbers */
    complex result;
    result.real = c1.real + c2.real;
    result.imaginary = c1.imaginary + c2.imaginary;
    return result;
}


