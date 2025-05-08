#include <stdio.h>
#include "parser.h"

int main () {
    InitData i = parse_init_file("init-ex.txt");
    Circuit circuit = parse_circ_file(i.n_qubits, "circ-ex.txt");
    
}