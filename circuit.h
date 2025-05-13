#ifndef CIRCUIT_H
#define CIRCUIT_H

#include "complex.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Represents a quantum circuit composed of qubits, gates, and its current state.
 */
typedef struct {
    unsigned int n_qubits;         /**< Number of qubits in the circuit */
    complex **gates[256];          /**< Array of up to 256 complex matrices representing gates */
    complex *state;                /**< Current quantum state vector */
    char *order;                   /**< Order in which gates are to be applied */
} Circuit;

/**
 * @brief Initializes the circuit by setting all gate pointers to NULL.
 *
 * @param c Pointer to the Circuit to initialize.
 */
void init_circuit(Circuit *c);

/**
 * @brief Applies a gate to the current state of the circuit.
 *
 * @param c Pointer to the Circuit.
 * @param gate_name Character identifying the gate (e.g. 'A', 'B', etc.).
 */
void apply_gate(Circuit *c, unsigned char gate_name);

/**
 * @brief Applies all gates in the specified order to the circuit state.
 *
 * @param c Pointer to the Circuit.
 */
void compute_circuit(Circuit *c);

/**
 * @brief Frees all memory allocated for the circuit, including gates, state, and order.
 *
 * @param c Pointer to the Circuit.
 */
void free_circuit(Circuit *c);

/**
 * @brief Prints the current quantum state of the circuit to stdout.
 *
 * @param c Pointer to the Circuit.
 */
void print_state(Circuit *c);

/**
 * @brief Prints the matrix corresponding to the specified gate.
 *
 * @param c Pointer to the Circuit.
 * @param gate_name Character identifying the gate.
 */
void print_gate(Circuit *c, unsigned char gate_name);

/**
 * @brief Prints all defined gates in the circuit.
 *
 * @param c Pointer to the Circuit.
 */
void print_all_gates(Circuit *c);

#endif
