# 🖥️ Processor

[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)
[![Languages](https://img.shields.io/github/languages/top/vanomark/Processor)](#)
[![Last Commit](https://img.shields.io/github/last-commit/vanomark/Processor)](#)

> A virtual stack-based processor simulator with a custom assembler, written in C/C++.

## 📋 Overview

This project implements a **virtual stack machine** with its own bytecode format and assembly-like language. It consists of two main components:

1. **Processor** (`Processor.cpp`) – A virtual CPU that executes bytecode from binary files
2. **Assembler** (`ASSEMBLER.cpp`) – A tool that converts human-readable assembly code into executable bytecode

### 🎯 Key Features

- **Stack-based architecture** – All operations work with a LIFO stack
- **8 General-purpose registers** (`ax`, `bx`, `cx`, `dx`, `ex`, `fx`, `gx`)
- **Conditional & unconditional jumps** – Support for control flow with labels
- **Debug mode** – Step-by-step execution visualization with colored output
- **Memory safety** – Extensive use of sanitizers (`-fsanitize=address`) and assertions
- **Custom bytecode format** – With signature and version checking
- 
---


## 🛠️ Requirements

- **Compiler**: `g++` with C++17 support
- **Make**: GNU Make
- **Platform**: Linux/macOS (POSIX-compatible)

---

## 🚀 Building & Running

### Build with Makefile

```bash
# Build the Assembler
make ass          # Release build
make assrun       # Run

# Build the Processor
make pro          # Release build
make prorun       # Run 

# Clean build artifacts
make clean
```


### Manual Compilation

```bash
# Compile Assembler
g++ src/ASSEMBLER.cpp -std=c++17 -O2 -Wall -Wextra -o ASSEMBLER.out

# Compile Processor
g++ src/Hash.cpp src/Processor.cpp src/StackCheck.cpp src/StackFunc.cpp \
    -std=c++17 -O2 -Wall -Wextra -o Processor.out
```

### Usage

```bash
# 1. Assemble: Convert .txt assembly to bytecode .bin
./ASSEMBLER.out [input.asm]           # Default: ASS_test_1.txt
# Output: PROGRAM_CODE.bin

# 2. Execute: Run the bytecode on the virtual processor
./Processor.out [PROGRAM_CODE.bin]    # Default: PROGRAM_CODE.bin
# Output: result.txt
```

---

## 📝 Assembly Language Reference

### Instructions

| Mnemonic | Opcode | Description | Example |
|----------|--------|-------------|---------|
| `PUSH <num>` | `0x01` | Push immediate value to stack | `PUSH 42` |
| `PUSHR <reg>` | `0x02` | Push register value to stack | `PUSHR ax` |
| `POP <reg>`  | `0x03` | Pop stack to register | `POP bx` |
| `ADD`        | `0x04` | Pop two values, push sum | `ADD` |
| `SUB`        | `0x05` | Pop two values, push difference | `SUB` |
| `MUL`        | `0x06` | Pop two values, push product | `MUL` |
| `DIV`        | `0x07` | Pop two values, push quotient | `DIV` |
| `SQRT`       | `0x08` | Pop value, push square root | `SQRT` |
| `JMP <label>`| `0x09` | Unconditional jump | `JMP loop` |
| `JB <label>` | `0x0A` | Jump if bottom (a > b) | `JB less` |
| `JA <label>` | `0x0B` | Jump if above (a < b) | `JA greater` |
| `JE <label>` | `0x0C` | Jump if equal | `JE done` |
| `OUT`        | `0x0D` | Pop and print value | `OUT` |
| `IN`         | `0x0E` | Read integer, push to stack | `IN` |
| `HLT`        | `0x0F` | Halt execution | `HLT` |
| `CALL <label>`| `0x10` | Call subroutine | `CALL func` |
| `RET`        | `0x11` | Return from subroutine | `RET` |

### Registers

```text
ax, bx, cx, dx, ex, fx, gx  // 7 general-purpose registers
```

### Labels & Control Flow

```asm
start:
    PUSH 10
    PUSH 5
    ADD
    OUT
    JMP end

end:
    HLT
```

### Example: Quadratic Equation Solver

See `QuadrSolver.txt` for a complete example that calculates roots of ax² + bx + c = 0.

---

## 🔧 Debug Mode

Enable debug output by compiling with debug flags:

```bash
make ass-d   # Assembler with debug
make pro-d   # Processor with debug
```

Debug features:
- 🎨 Colored terminal output for errors/warnings
- 📊 Visual instruction pointer indicator (`^`)
- 📋 Stack dump after each instruction
- ⏸️ Step-by-step execution (press Enter to continue)

---

## 📦 Bytecode Format

The compiled `.bin` files use a custom header:

```c
struct Header {
    uint32_t signature;  // Magic number for file validation
    uint32_t version;    // Bytecode version
    uint32_t size;       // Number of instructions
    uint32_t reserve;    // Reserved for future use
};
// Followed by: int code[size] – the actual instructions
```

---

## 🧪 Testing

Example test files included:
- `ASS_test_1.txt` – Basic arithmetic operations
- `ASS_test_2.txt` – Control flow with jumps
- `ASS_test_3.txt` – Register operations
- `QuadrSolver.txt` – Mathematical computation example

Run a test:
```bash
./ASSEMBLER.out ASS_test_1.txt
./Processor.out PROGRAM_CODE.bin
cat result.txt  # View output
```

---

## ⚠️ Notes & Limitations

- Stack overflow/underflow is checked but may cause abort in debug mode
- Division by zero is not explicitly handled – ensure valid input
- Maximum command size: `MAX_CMD` (defined in headers)
- Register indices are 1-based in assembly (`ax`=1, `bx`=2, etc.)

---



## 👨‍💻 Author

**vanomark** – [GitHub Profile](https://github.com/vanomark)

*This project was created for educational purposes to demonstrate virtual machine architecture and compiler design principles.*