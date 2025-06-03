# Quantum Circuit Simulator

This project is a simplified **Quantum Circuit Simulator** written in C. The simulator supports arbitrary quantum gates represented as matrices of complex numbers, and applies them to an initial state provided as input.

---

## 🧠 Project Structure

**The project is organized into the following files:**

- `main.c` – Main function: handles parsing, execution, and output of the circuit.
- `parser.c/.h` – Parser for input files containing initial state and circuit definitions.
- `circuit.c/.h` – Data structures and functions to build and execute the quantum circuit.
- `complex.c/.h` – Definition of the `complex` type and operations on complex numbers.
- `Makefile` – Build automation.

---

## ⚙️ Building

To compile the project, simply run:

```bash
make
```

This will compile all `.c` files and produce the executable `qsim`.

---

## ▶️ Execution

### With custom files

Run the simulator specifying the two input files:

```bash
./qsim [init_file] [circuit_file]
```

Example:

```bash
./qsim init-ex.txt circ-ex.txt
```

### Without arguments

If no arguments are provided, the program uses the default files in the current directory:

- `init-ex.txt`
- `circ-ex.txt`

```bash
./qsim
```

---

## 🗂️ Input File Format

### `init-ex.txt` – Initial State

```txt
#qubits 1

#init [0.5+i0.5, 0.5-i0.5]
```

- `#qubits`: number of qubits (integer ≥ 1).
- `#init`: vector of complex numbers in square brackets, separated by commas.

  - Supported formats: `a+ib`.
  - `a` and `b` are any real number in the form of `int_part.decimal_part` e.g. `-3.91`

### `circ-ex.txt` – Circuit Definition

```txt
#define X [(0, 1) (1, 0)]

#define I [(1, 0) (0, 1)]

#define Y [(0, -i) (i, 0)]

#circ Y X I
```

- `#define <letter>`: defines a square matrix of size `2^n x 2^n` (quantum gate). `<letter>` must be a single ASCII character.
- `#circ`: sequence of letters representing the gates to apply to the initial state in order.

---

## 🖨️ Output

The simulator prints to stdout:

**Final State**: complex vector resulting from sequentially applying the gates to the initial state.

---

## ❗ Notes

- Gate matrices must be **square** and compatible with the specified number of qubits.
- Complex numbers are printed in the form `a+ib`.

---

## 👨‍💻 Author

**Vincenzo**
Computer Science Student – Sapienza University of Rome
