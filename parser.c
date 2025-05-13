#include "parser.h"

char *read_line(FILE* fptr) {
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
    buffer[i] = fgetc(fptr); /* including '\n' */
    
    return buffer;
}

void trim_string(char **str, char s_char, char e_char) {
    char *start = strchr(*str, s_char);
    char *end = strchr(*str, e_char); 

    *str = start + 1;
    (*str)[end - start - 1] = '\0';
}


complex parse_complex(char *token) {
    unsigned int l = strlen(token);
    while(*token == ' ') { /* deleting spaces */
        token += 1;
    }
    char *i_ptr = strchr(token, 'i'); /* pointer to 'i' letter */

    double i_sign = 1.0;
    double i_value = 0.0;
    double r_value = 0.0;
    
    char *end;
    r_value = strtod(token, &end); /* parses real part if any */
    if (i_ptr != NULL) {
        if(i_ptr > token) { /* if a != 0 or b < 0*/
            i_sign = *(i_ptr - 1) == '-' ? -1.0 : 1.0 ;
        }
        if (i_ptr + 1 < token + l - 1) { /* if b != 1*/
            i_value = strtod(i_ptr + 1, NULL);
        }
        i_value = i_value == 0 ? 1 : i_value; /* handles implicit 1 (e.g. a+i)  */
        i_value = i_sign * i_value;
    }
    complex c;
    c.imaginary = i_value;
    c.real = r_value;
    return c;
}

Circuit parse_init_file(char *path) {
    FILE* fptr = fopen(path, "r");
    
    Circuit  c;
    if (fptr != NULL) {
        init_circuit(&c);
        
        char *line = NULL;
        line = read_line(fptr);
        if(sscanf(line, "#qubits %i", &c.n_qubits)) {; /* reads number of quibits */
            free(line);
            line = read_line(fptr);

            if(strncmp(line, "#init ", 6) == 0) {
                complex *s = malloc((1 << c.n_qubits ) * sizeof(complex) ); /* allocating 2^n init state vector  */
                char *copy = line; /* making a copy in order to free with the original ptr (line) */
                trim_string(&copy, '[', ']');
        
                char *token = strtok(copy, ",");
                unsigned long int n = 1 << c.n_qubits;
                unsigned int i = 0;
                while (i < n && token != NULL) {
                    s[i] = parse_complex(token); /* parsing i-th  complex number*/
                    i++;
                    token = strtok(NULL, ","); /* getting next token */
                } 
                free(line);
                c.state = s;
                fclose(fptr);
            } else {
                fprintf(stderr, "Error: #init directive is misformatted %s\n",line);
                exit(EXIT_FAILURE);
            }
        } else {
            fprintf(stderr, "Error: #qubits directive is misformatted %s\n", line);
            exit(EXIT_FAILURE);
        }
    } else {
        fprintf(stderr, "Error: couldn't open init file at %s\n", path);
        exit(EXIT_FAILURE);
    }
    return c;
}

void parse_circ_file(Circuit *circuit, char *path) {
    FILE *fptr = fopen(path, "r");
    if (fptr != NULL) {
        char *line = read_line(fptr);
        char *copy;
        unsigned char key;
        while(sscanf(line, "#define %c", &key)) { /* parsing each #define directive */
            copy = line;
            trim_string(&copy, '[', ']');
            circuit->gates[key] = parse_matrix(copy, 1 << circuit->n_qubits);
            free(line);
            line = read_line(fptr);
        }
        copy = line;
        copy += 6; /* skip "#circ " */
        unsigned long int i = 0;
        unsigned int b_size = 128;
        char *order = malloc(128);
        char *token = strtok(copy, " ");
        while (token != NULL) { /* read each letter after #circ */
            if (i >= b_size-1) {
                b_size <<= 1;
                order = realloc(order, b_size);
            }
            order[i] = *token;
            token = strtok(NULL, " ");
            i++;
        }
        free(line);
        fclose(fptr);
        order[i] = '\0';
        circuit->order = order;
    } else {
        fprintf(stderr, "Error: couldn't open circ file at %s\n", path);
        exit(EXIT_FAILURE);
    }
}


complex** parse_matrix(char *str, unsigned int n) {
    complex **m = malloc(n * sizeof(complex*)); /* matrix is an array of n ptrs to complex arrays */
    
    unsigned int i = 0;/* row index */
    unsigned int j = 0;/* col index */
    
    while (i < n) {
        m[i] = malloc(n * sizeof(complex)); /* m[i] is an array of n complex numbers */

        char *r_start = strchr(str, '(') + 1;
        char *r_end = strchr(str, ')');
        unsigned int l = r_end - r_start;

        char *r_buf = malloc(l * sizeof(char));/* dynamic buffer*/
        strncpy(r_buf, r_start, l);
        r_buf[l] = '\0';
        
        char *saveptr;
        char *token = strtok_r(r_buf, ",", &saveptr);
        while(j < n) {
            m[i][j] = parse_complex(token); /* populating the matrix */
            token = strtok_r(NULL, ",", &saveptr);
            j++;
        }
        j = 0;
        i++;
        free(r_buf);
        str = r_end + 1;
    }
    return m;
}

