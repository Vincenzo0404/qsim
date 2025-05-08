#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "complex.h"
#include "circuit.h"
#include "complex_matrix.h"

typedef struct {
    int n_qubits;
    complex *init_state;
} InitData;



InitData parse_init_file(char filename[]);
complex parse_complex(char *token);
Circuit parse_circ_file(unsigned int n_qubits, char filename[]);

#endif