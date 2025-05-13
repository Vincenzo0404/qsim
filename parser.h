#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "complex.h"
#include "circuit.h"

/**
 * @brief Parses an initialization file containing circuit information.
 *
 * The file must contain '#qubits' and '#init' state vector.
 * 
 * @param path Path to the initialization file.
 * @return Circuit structure initialized from the file.
 */
Circuit parse_init_file(char *path);

/**
 * @brief Parses a complex number in the form "a+ib".
 *
 * @param token The string representing the complex number.
 * @return A complex number parsed from the string.
 */
complex parse_complex(char *token);

/**
 * @brief Parses a circuit file containing gate definitions and gate order.
 *
 * The file should contain `#define` sections for gate matrices, and a `#circuit` section
 * indicating the order of application.
 *
 * @param circuit Pointer to a Circuit structure to be populated.
 * @param path Path to the circuit definition file.
 */
void parse_circ_file(Circuit *circuit, char *path);

/**
 * @brief Reads a full line from a file.
 *
 * Dynamically allocates a buffer and returns a null-terminated string.
 * The returned string must be freed by the caller.
 *
 * @param fptr A pointer to an open file.
 * @return A dynamically allocated string containing the line (excluding the newline character).
 */
char *read_line(FILE *fptr);

/**
 * @brief Trims a string in-place between two given characters.
 *
 * Adjusts the pointer to point to the substring between `s_char` and `e_char`.
 * Null-terminates the string at the closing character.
 *
 * @param str Pointer to the string pointer to be trimmed.
 * @param s_char Starting delimiter (e.g. '[').
 * @param e_char Ending delimiter (e.g. ']').
 */
void trim_string(char **str, char s_char, char e_char);

/**
 * @brief Parses a matrix of complex numbers from a string.
 * 
 * @param str The string representing the matrix.
 * @param n The number of rows and columns (assumes n x n square matrix).
 * @return A dynamically allocated 2D array of complex numbers.
 */
complex** parse_matrix(char *str, unsigned int n);

#endif