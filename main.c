#include <stdio.h>
#include "parser.h"

int main () {
    Circuit c = parse_init_file("init-ex.txt");
    parse_circ_file(c, "circ-ex.txt");
    
}