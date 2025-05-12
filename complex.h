#ifndef COMPLEX_H
#define COMPLEX_H

typedef struct {
    double real;
    double imaginary;
} complex;

complex vector_mul(complex *v1, complex *v2, unsigned int n);
complex complex_mul(complex c1, complex c2);
complex complex_sum(complex c1, complex c2);

#endif