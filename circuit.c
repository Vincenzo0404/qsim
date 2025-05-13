#include "circuit.h"

void init_circuit(Circuit *c) {
    for (unsigned int i = 0; i < 256; i++) { /* intializing all gate pointers to NULL */
        c->gates[i] = NULL;
    }
}

void apply_gate(Circuit *c, unsigned char gate_name) {
    complex **gate = c->gates[gate_name];
    if (gate == NULL) { /* checking if gate "gate_name" exists */
        fprintf(stderr,"Error: gate %c is not defined. \n", gate_name);
        exit(EXIT_FAILURE);
    }    
    unsigned long int n = 1 << c->n_qubits;
    complex *new_state = malloc(n * sizeof(complex)); /* the new state vector */
    for (unsigned long int i = 0; i < n; i++) { /* computing matrix vector product */
        new_state[i] = complex_vector_mul(gate[i], c->state, n);
    }
    free(c->state);
    c->state = new_state;
}

void compute_circuit(Circuit *c) {
    unsigned int l = strlen(c->order);
    for (unsigned int i = 0; i < l; i++) { /* for each character i in c->order apply gate[i] to the state vectore*/
        apply_gate(c, (unsigned char) c->order[i]);
    }
}
void free_circuit(Circuit *c) {
    unsigned long int n = 1 << c->n_qubits; 
    for (int i = 0; i < 256; i++) { /* for each gate */
        if (c->gates[i] != NULL) {
            for (unsigned long int j = 0; j < n; j++) {/* free all arrays of the gate */
                if (c->gates[i][j] != NULL) {
                    free(c->gates[i][j]);
                }
            }
            free(c->gates[i]);/* free the gate */
        }
    }
    free(c->state);/* free the state vector */
    free(c->order)/* free the order string */;
}


void print_state(Circuit *c) {
    for (unsigned long int i = 0; i < 1 << c->n_qubits; i++) {
        complex_print(c->state[i]);
        printf("\n");
    }
}

void print_gate(Circuit *c, unsigned char gate_name) {
    if (c->gates[gate_name] == NULL) {
        printf("Gate '%c' not defined.\n", gate_name);
        exit(EXIT_FAILURE);
    }

    unsigned long int n = 1 << c->n_qubits;
    complex **gate = c->gates[gate_name];

    for (unsigned long int i = 0; i < n; i++) {
        for (unsigned long int j = 0; j < n; j++) {
            complex_print(gate[i][j]);
            printf(" ");
        }
        printf("\n");
    }
}

void print_all_gates(Circuit *c) {
    for (int i = 0; i < 256; i++) {
        if (c->gates[i] != NULL) {
            printf("Gate '%c':\n", (char)i);
            print_gate(c, (unsigned char)i);
            printf("\n");
        }
    }
}

