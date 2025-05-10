#ifndef CIRCUIT_H
#define CIRCUIT_H

typedef struct {
    unsigned int n_qubits;
    complex ***matrices; /* an array of matrices */
    complex *state; /* current circuit's state */
    char *order;
} Circuit;

#endif