#ifndef ASSEMBLER
#define ASSEMBLER


#include <assert.h>
#include <stdio.h>
#include <string.h>

enum ass_command {
    PUSH = 1,
    ADD  = 2,
    SUB  = 3,
    MUL  = 4,
    DIV  = 5,
    OUT  = 6,
    HLT  = 0,
};

const size_t MIN_STR_SIZE = 50;
const size_t MAX_CMD = 100;

int    RunASS         (const char *asm_file, FILE *out_file);
size_t tell_file_size (FILE *);

#endif