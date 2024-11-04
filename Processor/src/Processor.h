#ifndef PROCESSORH
#define PROCESSORH

// #include <TXLib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#include "StackFunc.h" 
#include "StackCheck.h"
#include "Hash.h"

#ifdef PROCESSOR_DEBUG
    #define ON_DEBUG(code) code

#else   
    #define ON_DEBUG(code)

#endif /* DEBUG */

enum regs {
    AX = 1,
    BX = 2,
    CX = 3,
    DX = 4,
    EX = 5,
    FX = 6,
    GX = 7,
};

enum ass_command {
    PUSH  = 1,
    ADD   = 2,
    SUB   = 3,
    MUL   = 4,
    DIV   = 5,
    OUT   = 6,
    IN    = 7,
    JMP   = 8,
    JB    = 9,
    JA    = 10,
    PUSHR = 11,
    POP   = 12,
    CALL  = 13,
    RET   = 14,
    HLT   = -1,
};

struct SPU {
    int *code;
    int *RAM;
    size_t ip;
    size_t size;
    Stack Stk;
    register_t *registers;
};

int Process     (SPU *Proc);
int SPUctor     (SPU *Proc, const char* code_file);
int SPUdtor     (SPU *Proc);
int CodeInit    (const char *name_of_file, int **code, size_t *size);
int ProcDump    (SPU *Proc);
int set_bird    (size_t ip, size_t factor);
int put_symbols (char symbol, size_t amount);

const size_t MAX_CMD = 100;
const size_t REGISTER_SIZE = 8;
const size_t CODE_SIZE = 25;
const size_t SIGNATURE_SIZE = 10;
const size_t VERSION_SIZE = 5;

const u_int32_t  VERSION    = 2;
const u_int32_t  SIGNATURE  = 0x3433524F;

const char* OUTPUT_FILE = "result.txt";

#endif /* PROCESSORH */