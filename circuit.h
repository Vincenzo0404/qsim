#ifndef CIRCUIT_H
#define CIRCUIT_H

#include "complex.h"
#include <string.h>
#include <stdlib.h>

typedef struct {
    unsigned int n_qubits;
    complex **gates[256]; /* an array of 256 matrices */
    complex *state; /* current circuit's state */
    char *order;
} Circuit;

void apply_gate(Circuit *c, unsigned char gate_name);
void compute_circuit(Circuit *c);
void free_circuit(Circuit *c);
void print_state(Circuit *c);

#endif