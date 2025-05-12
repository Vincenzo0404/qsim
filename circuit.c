#include "circuit.h"

void apply_gate(Circuit *c, unsigned char gate_name) {
    unsigned long int n = 1 << c->n_qubits;
    complex **gate = c->gates[gate_name];
    complex *new_state = malloc(n * sizeof(complex));
    for (unsigned long int i = 0; i < n; i++) {
        new_state[i] = complex_vector_mul(gate[i], c->state, n);
    }
    free(c->state);
    c->state = new_state;
}

void compute_circuit(Circuit *c) {
    unsigned int l = strlen(c->order);
    for (unsigned int i = 0; i < l; i++) {
        apply_gate(c, c->order[i]);
    }
}

void free_circuit(Circuit *c) {
    unsigned long int n = 1 << c->n_qubits;
    for (int i = 0; i < 256; i++) {
        for (unsigned long int j = 0; j < n; j++) {
            free(c->gates[i][j]); 
        }
        free(c->gates[i]);
    }
}

void print_state(Circuit *c) {
    for (unsigned long int i = 0; i < 1 << c->n_qubits; i++) {
        complex_print(c->state[i]);
    }
}