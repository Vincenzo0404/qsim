#ifndef COMPLEX_H
#define COMPLEX_H

#include <stdio.h>

/**
 * @brief Structure representing a complex number.
 */
typedef struct {
    double real;       /**< Real part */
    double imaginary;  /**< Imaginary part */
} complex;

/**
 * @brief Computes the dot product of two complex vectors.
 *
 * This function performs the sum of element-wise products between
 * two complex vectors of length n: result = ∑ (v1[i] * v2[i])
 *
 * @param v1 First complex vector.
 * @param v2 Second complex vector.
 * @param n Length of the vectors.
 * @return Resulting complex number from the dot product.
 */
complex complex_vector_mul(complex *v1, complex *v2, unsigned long long int n);

/**
 * @brief Multiplies two complex numbers.
 *
 * @param c1 First complex number.
 * @param c2 Second complex number.
 * @return Result of the multiplication (c1 * c2).
 */
complex complex_mul(complex c1, complex c2);

/**
 * @brief Sums two complex numbers.
 *
 * @param c1 First complex number.
 * @param c2 Second complex number.
 * @return Result of the addition (c1 + c2).
 */
complex complex_sum(complex c1, complex c2);

/**
 * @brief Prints a complex number to stdout.
 *
 * The number is printed in the form "a+ib".
 *
 * @param c Complex number to print.
 */
void complex_print(complex c);

#endif // COMPLEX_H
