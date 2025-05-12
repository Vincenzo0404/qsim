#include "parser.h"

complex parse_complex(char *token) {
    /* Parses a complex number in the form of "a+ib" */
    unsigned int l = strlen(token);
    while(*token == ' ') { /* deleting spaces */
        token += 1;
    }
    char *i_ptr = strchr(token, 'i');

    double i_sign = 1.0;
    double i_value = 0.0;
    double r_value = 0.0;
    
    char *end;
    r_value = strtod(token, &end);
    if (i_ptr != NULL) {
        if(i_ptr > token) {/*checking imag part's sign  */
            i_sign = *(i_ptr - 1) == '-' ? -1.0 : 1.0 ;
        }
        if (i_ptr + 1 < token + l - 1) { /* checking imag part's value */
            i_value = strtod(i_ptr + 1, NULL);
        }
        i_value = i_sign * i_value;
    }
    complex c;
    c.imaginary = i_value;
    c.real = r_value;
    return c;
}

Circuit parse_init_file(char filename[]) {
    /* initializes the circuit with n_qubits and init state */
    FILE* fptr = fopen(filename, "r");
    Circuit c;
    
    if (fptr != NULL) {

        unsigned int n_chars = 80;
        char content[n_chars];

        fgets(content, n_chars, fptr);
        sscanf(content, "#qubits %i", &c.n_qubits); /* reads number of quibits */

        complex *s = malloc((1 << c.n_qubits ) * sizeof(complex) ); /* allocating 2^n complex numbers  */
    /* TODO deallocare s */
        fgets(content, n_chars, fptr);
        fgets(content, n_chars, fptr); 

        trim_string(content);

        char *token = strtok(content, ",");
        unsigned int i = 0;
        while (token != NULL) {
            s[i] = parse_complex(token); /* parsing i-th  complex number*/
            i++;
            token = strtok(NULL, ","); /* getting next token */
        }
        c.state = s;
        fclose(fptr);
    } else {
        printf("%s", "couldn't open file init");
    }
    return c;
}

void trim_string(char* str) {
    char *start = strchr(str, '[');
    char *end = strchr(str, ']'); 

    unsigned int len = end - start - 1;

    strncpy(str, start + 1, len);
    str[len] = '\0';
}

void parse_circ_file(Circuit circuit, char filename[]) {
    /* parses circ file and computes  */

    FILE *fptr = fopen(filename, "r");
    char *line = read_line(fptr);
    unsigned char key;
    while(line[0] == '\n' || sscanf(line, "#define %c", &key)) {
        trim_string(line);
        circuit.matrices[key] = parse_matrix(line, 1 << circuit.n_qubits);
        free(line);
        line = read_line(fptr);
    }
}

char *read_line(FILE* fptr) {
    /* reads a whole line from fptr */
    unsigned int b_size = 256;
    unsigned int i = 0;
    char *buffer = malloc(b_size);
    char c = fgetc(fptr);
    while(c != '\n' && c != EOF) {
        buffer[i] = c;
        if (i == b_size - 2) { /* reallocating memory for dynamic buffer */
            b_size <<= 1;
            buffer = realloc(buffer, b_size);
        }
        c = fgetc(fptr);
        i++;
    }
    buffer[i] = '\0';
    return buffer;
}

complex** parse_matrix(char *str, unsigned int n) {
    complex **m = malloc(n * sizeof(complex*)); /* matrix is an array of n ptrs to complex arrays */
    
    unsigned int i = 0;/* row index */
    unsigned int j = 0;/* col index */

    while (i < n) {
        char *r_start = strchr(str, '(') + 1;
        char *r_end = strchr(str, ')');
        unsigned int l = r_end - r_start;

        char *r_buf = malloc(l * sizeof(char));
        strncpy(r_buf, r_start, l);
        r_buf[l] = '\0';
        
        char *saveptr;
        char *token = strtok_r(r_buf, ",", &saveptr);
        while(j < n) {
            m[i][j] = parse_complex(token);
            token = strtok_r(NULL, ",", &saveptr);
            j++;
        }
        j = 0;
        i ++;
        free(r_buf);
        str = r_end + 1;
    }
    return m;
}

