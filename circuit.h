#ifndef CIRCUIT_H
#define CIRCUIT_H
#include "complex_matrix.h"

typedef struct {
    unsigned int n_qubits;
    complex *matrices;
    char *order;
} Circuit;

#endif