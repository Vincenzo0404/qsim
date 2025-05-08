#include "parser.h"

complex parse_complex(char *token) {
    double r_sign = *token == '-' ? -1.0 : 1.0; /* real part sign */

    char *imag_sign_ptr = strpbrk(token + 1, "+-");
    double i_sign = *imag_sign_ptr == '+' ? 1 : -1 ; /* imaginary part sign */

    complex c;

    c.real = r_sign*strtod(token, &imag_sign_ptr); /* casting string to doubles for real and imaginary parts */
    c.imaginary = i_sign*strtod(imag_sign_ptr + 2, NULL);

    return c;
}

InitData parse_init_file(char filename[]) {
    
    FILE* fptr = fopen(filename, "r");
    InitData d;
    
    if (fptr != NULL) {

        unsigned int n_chars = 80;
        char content[n_chars];

        fgets(content, n_chars, fptr);
        sscanf(content, "#qubits %i", &d.n_qubits); /* reads number of quibits */

        complex *s = malloc((1 << d.n_qubits ) * sizeof(complex) ); /* allocating 2^n complex numbers  */
        if (s == NULL) {
            printf("%s", "allocazione memoria fallita");
        }
        
        fgets(content, n_chars, fptr);
        fgets(content, n_chars, fptr); 

        char *start = strchr(content, '[');/* points to the beginning of the values */
        char *end = strchr(content, ']'); /* points to the end of the values */

        unsigned int len = end - start;
        char trimmed[len];

        strncpy(trimmed, start + 1, len - 1); /* copying  only the values in trimmed*/
        trimmed[len - 1] = '\0';

        char *token = strtok(trimmed, ",");
        unsigned int i = 0;
        while (token != NULL) {
            s[i] = parse_complex(token); /* parsing i-th  complex number*/
            i++;
            token = strtok(NULL, ","); /* getting next token */
        }
        d.init_state = s;
    }
    fclose(fptr);
    return d;
}

void parse_circ_file(char filename[]) {

}

