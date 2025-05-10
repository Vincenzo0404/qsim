#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "complex.h"
#include "circuit.h"

Circuit parse_init_file(char filename[]);
complex parse_complex(char *token);
void parse_circ_file(Circuit circuit, char filename[]);
char *read_line(FILE *fptr);
void trim_string(char* str);
complex** parse_matrix(char *str, unsigned int n);
#endif