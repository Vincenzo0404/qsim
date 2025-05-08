#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "complex.h"

typedef struct {
    int n_qubits;
    complex *init_state;
} InitData;

InitData parse_init_file(char filename[]);
complex parse_complex(char *token);
void parse_circ_file(char filename[]);

#endif