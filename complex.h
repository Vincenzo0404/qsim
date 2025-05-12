#ifndef COMPLEX_H
#define COMPLEX_H

#include <stdio.h>

typedef struct {
    double real;
    double imaginary;
} complex;

complex complex_vector_mul(complex *v1, complex *v2, unsigned int n);
complex complex_mul(complex c1, complex c2);
complex complex_sum(complex c1, complex c2);
void complex_print(complex c);
#endif