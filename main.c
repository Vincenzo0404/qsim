#include <stdio.h>
#include "parser.h"

int main () {
    Circuit c = parse_init_file("init-ex.txt");
    parse_circ_file(&c, "circ-ex.txt");
    compute_circuit(&c);
    print_state(&c);
/*     free_circuit(&c); */
}