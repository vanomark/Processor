#ifndef ASSEMBLERH
#define ASSEMBLERH

const size_t     MAX_CMD       = 200;
const size_t     MIN_STR_SIZE  = 50;
const size_t     MARKER_AMOUNT = 10;
const size_t     MARKER_SIZE   = 12;
const u_int32_t  VERSION       = 4;
const u_int32_t  SIGNATURE     = 0x3433524F;
const u_int32_t  EASTER        = 0x41444544;

#ifdef ASM_DEBUG
    #define ON_DEBUG(code) code

#else   
    #define ON_DEBUG(code)

#endif /* ASM_DEBUG */

const char* _PUSHNUM_ = "push";
const char* _PUSHREG_ = "pushr";
const char* _ADD_     = "add";
const char* _SUB_     = "sub";
const char* _MUL_     = "mul";
const char* _DIVIDE_  = "div";
const char* _OUTPUT_  = "out";
const char* _INPUT_   = "in";
const char* _JUMP_    = "jmp";
const char* _JUMP_B_  = "jb";
const char* _JUMP_A_  = "ja";
const char* _JUMP_E_  = "je";
const char* _POP_     = "pop";
const char* _CALL_    = "call";
const char* _RETURN_  = "ret";
const char* _HLT_     = "hlt";
const char* _SQRT_    = "sqrt";


enum regs {
    AX = 1,
    BX = 2,
    CX = 3,
    DX = 4,
    EX = 5,
    FX = 6,
    GX = 7,
    REG_ERROR = -1,
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
    JE    = 15,
    PUSHR = 11,
    POP   = 12,
    CALL  = 13,
    RET   = 14,
    SQRT  = 16,
    HLT   = -1,
};

struct Header {
    u_int32_t sig;
    u_int32_t ver;
    u_int32_t size;
    u_int32_t reserved;
};

struct marker {
    int index;
    char name[MARKER_SIZE];
};

struct ASSEMBLER {
    size_t ip;
    int *code;
    marker labels[MARKER_AMOUNT];
};

const int   POISON_VALUE = -1;
const char* POISON_NAME  = "DEDLOH";

const char* DEFAULT_ASMFILE = "Factorial.txt";
const char* DEFAULT_OUTFILE = "program.bin";

int    Assemble          (const char *asm_file, ASSEMBLER *ASM);
int    Get_reg_num       (const char* xx);
int    Outstream         (const char* filename, ASSEMBLER *ASM);
int    Skip_comments     (char *);
int    Labelput          (ASSEMBLER *ASM, const char *mark);
int    ASMCtor           (ASSEMBLER *ASM, size_t size);
int    ASMDtor           (ASSEMBLER *ASM);  
int    ASMDump           (ASSEMBLER *ASM);
size_t Labelfind         (ASSEMBLER *ASM, const char *str);
size_t Get_file_size     (FILE *);



#endif /* ASSEMBLERH */