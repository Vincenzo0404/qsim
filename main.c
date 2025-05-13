#include <stdio.h>
#include "parser.h"

int main (int argc, char **argv) {
    char *init_file;
    char *circuit_file;
    if (argc == 3) {
        init_file = argv[1];
        circuit_file = argv[2];
    } else {
        fprintf(stderr, "Warning: you must specify 2 input files (init and circ). Using default (init-ex.txt and circ-ex.txt)\n");
        init_file = "init-ex.txt";
        circuit_file = "circ-ex.txt";
    }

    Circuit c = parse_init_file(init_file);
    parse_circ_file(&c, circuit_file);
    print_all_gates(&c);
    compute_circuit(&c);
    print_state(&c);
    free_circuit(&c);
    return 0;
}