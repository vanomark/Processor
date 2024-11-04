// #define ASM_DEBUG

#include "ASSEMBLER.h"
#include "ColorPrintFile.h"

int main(const int argc, const char* argv[]) 
{   
    ASSEMBLER ASM = {};
    ASMCtor(&ASM, MAX_CMD);

    if (argc == 1) {
        fprintf(stderr, "WARNING: A file haven't given, so default asmfile will be used.\n");
        Assemble("ass_test1.txt", &ASM);
    } else {
        Assemble(argv[1], &ASM);
    }
    
    Outstream("PROGRAM_CODE.txt", &ASM); 
    ASMDtor(&ASM);

    return 0;
}

int Assemble(const char *asm_file, ASSEMBLER *ASM)
{   
    assert(ASM);

    int asm_count = 0;
    while (asm_count++ < 2) {
        FILE *ReadFile = NULL;

        if ((ReadFile = fopen(asm_file, "r")) == 0) {

            if (asm_count == 1) {
                fprintf(stderr, "WARNING: A wrong file was given, so default asmfile will be used.\n");
            }
            ReadFile = fopen("ass_test1.txt", "r");

            if (ReadFile == NULL) {
                fprintf(stderr, "ERROR:   Couldn't open default asm file.\n");

                return -1;
            }
        }

        if (asm_count == 2) {
            ASM->ip = 0;
        }

        ON_DEBUG(RED_PRINT_LOG(stderr, "asm_count = %d, ip = %lu\n", asm_count, ASM->ip));

        while(ASM->ip < MAX_CMD) { 
            ON_DEBUG(fprintf(stderr, "You need some brain\n"));

            ON_DEBUG(ASMDump(ASM));

            char cmd[MIN_STR_SIZE] = "";
            fscanf(ReadFile, "%s", cmd);

            // if (Skip_comments(cmd))
            //     continue;

            if (strlen(cmd) < 2) {
                break;
            }

            if (char *ptr = strchr(cmd, ':')) {
                char str[MIN_STR_SIZE] = {};
                
                ON_DEBUG(CYAN_PRINT_LOG(stderr, "%s\n", str));

                memcpy(str, cmd, size_t(ptr) - size_t(cmd));

                ON_DEBUG(CYAN_PRINT_LOG(stderr, "%s\n", str));

                Labelput(ASM, str);

                ON_DEBUG(CYAN_PRINT_LOG(stderr, "%s\n", str));
                continue;
            }

            if (strcmp(cmd, "push") == 0) {
                int arg = 0;

                if (fscanf(ReadFile, "%d", &arg) == 0) {
                    fprintf(stderr, "ERROR CODE: 1488\n");
                }

                ASM->code[ASM->ip++] = PUSH;
                ASM->code[ASM->ip++] = arg;
                continue;
            }

            if (strcmp(cmd, "pushr") == 0) {
                int arg = 0;

                fscanf(ReadFile, "%s", cmd); //todo lowercase
                arg = Get_reg_num(cmd);

                if (arg == REG_ERROR) {
                    fprintf(stderr, "Welcome to the FightClub\n");
                    break;
                }

                ASM->code[ASM->ip++] = PUSHR;
                ASM->code[ASM->ip++] = arg;
                continue;
            }

            if (strcmp(cmd, "pop") == 0) {
                int arg = 0;

                fscanf(ReadFile, "%s", cmd); //todo lowercase
                arg = Get_reg_num(cmd);

                if (arg == REG_ERROR) {
                    fprintf(stderr, "Welcome to the FightClub\n");
                    break;
                }

                ASM->code[ASM->ip++] = POP;
                ASM->code[ASM->ip++] = arg;
                continue;
            }

            if (strcmp(cmd, "add") == 0) {
                ASM->code[ASM->ip++] = ADD;
                continue;
            }

            if (strcmp(cmd, "sub") == 0) {
                ASM->code[ASM->ip++] = SUB;
                continue;
            }

            if (strcmp(cmd, "mul") == 0) {
                ASM->code[ASM->ip++] = MUL;
                continue;
            }

            if (strcmp(cmd, "div") == 0) {
                ASM->code[ASM->ip++] = DIV;
                continue;
            } 

            if (strcmp(cmd, "out") == 0) {
                ASM->code[ASM->ip++] = OUT;
                continue;
            }

            if (strcmp(cmd, "in") == 0) {
                ASM->code[ASM->ip++] = IN;
                continue;
            }
            
            if (strcmp(cmd, "jmp") == 0) {
                int arg = -1;

                if (fscanf(ReadFile, "%d", &arg) == 0) {
                    char marker[MARKER_SIZE];
                    fscanf(ReadFile, "%s", marker);
                    arg = ASM->labels[Labelfind(ASM, marker)].index;
                }

                ASM->code[ASM->ip++] = JMP;
                ASM->code[ASM->ip++] = arg;
                continue;
            }

            if (strcmp(cmd, "jb") == 0) {
                int arg = -1;

                if (fscanf(ReadFile, "%d", &arg) == 0) {
                    char marker[MARKER_SIZE] = {};
                    fscanf(ReadFile, "%s", marker);

                    ON_DEBUG(RED_PRINT_LOG(stderr, "%d\n", arg));

                    arg = ((ASM->labels)[Labelfind(ASM, marker)]).index;
                }

                ON_DEBUG(RED_PRINT_LOG(stderr, "%d\n", arg));

                ASM->code[ASM->ip++] = JB;
                ASM->code[ASM->ip++] = arg;
                continue;
            }

            if (strcmp(cmd, "ja") == 0) {
                int arg = 0;

                if (fscanf(ReadFile, "%d", &arg) == 0) {
                    char *marker = (char *) calloc(MARKER_SIZE, sizeof(char));
                    fscanf(ReadFile, "%s", marker);
                    arg = ASM->labels[Labelfind(ASM, marker)].index;
                }

                ASM->code[ASM->ip++] = JA;
                ASM->code[ASM->ip++] = arg;
                continue;
            }

            if (strcmp(cmd, "hlt") == 0) {
                ASM->code[ASM->ip++] = HLT;
                continue;
            }

            fprintf(stderr, "Syntax error\n");
            fprintf(stderr, "IP = %lu", ASM->ip);
            break;
        }
        
        fclose(ReadFile);
    }

    return 0;
}

////====================================================================================================================

int Get_reg_num(const char* xx)
{
    if (strcmp(xx, "ax") == 0) 
        return AX;

    if (strcmp(xx, "bx") == 0) 
        return BX;

    if (strcmp(xx, "cx") == 0) 
        return CX;

    if (strcmp(xx, "dx") == 0) 
        return DX;

    if (strcmp(xx, "ex") == 0) 
        return EX;

    if (strcmp(xx, "fx") == 0) 
        return FX;

    if (strcmp(xx, "gx") == 0) 
        return GX;

    return REG_ERROR;
}

int Outstream(const char* filename, ASSEMBLER *ASM)
{
    FILE *out_file = fopen(filename, "wb");

    assert(ASM);
    assert(ASM->code);
    assert(out_file);
    assert(filename);
    
    Header hdr = {SIGNATURE, VERSION, (u_int32_t) ASM->ip, EASTER};

    // fputs(SIGNATURE, out_file);
    // fputs(VERSION,   out_file);
    // fprintf(out_file, "%lu\n", ASM->ip);

    fwrite(&hdr, 1, sizeof(hdr), out_file);
    fwrite(ASM->code, ASM->ip, sizeof(ASM->code[0]), out_file);

    // for (size_t i = 0; i < ASM->ip; i++)
    //     fprintf(out_file, "%d", ASM->code[i]);

    fclose(out_file);

    return 0;
}

int Labelput(ASSEMBLER *ASM, const char *str)
{   
    assert(ASM);
    assert(str);

    size_t result_index = 0;

    if ((result_index = Labelfind(ASM, str)) == (size_t) -1) {
        for (size_t i = 0; i < MARKER_AMOUNT; i++) {
            if (ASM->labels[i].index == POISON_VALUE) {
                memcpy((ASM->labels[i]).name, str, MARKER_SIZE * sizeof(char));
                ASM->labels[i].index = (int) ASM->ip;

                ON_DEBUG(ASMDump(ASM));

                break;
            }
        }
    } else {
        ASM->labels[result_index].index = (int) ASM->ip;
    }

    return 0;
}

size_t Labelfind(ASSEMBLER *ASM, const char *str) 
{
    assert(ASM);
    assert(str);

    for (size_t i = 0; i < MARKER_AMOUNT; i++) {
        if (strcmp(ASM->labels[i].name, str) == 0) {

            ON_DEBUG(CYAN_PRINT_LOG(stderr, "i = %d\n", i));

            return i;
        }
    }
    
    return (size_t) -1;
}

int ASMCtor(ASSEMBLER *ASM, size_t size) 
{   
    assert(ASM);

    ASM->ip = 0;
    ASM->code = (int *) calloc(size, sizeof(int)); // todo /////////////////////////////////////////////////////////////

    for (size_t i = 0; i < MARKER_AMOUNT; i++) {
        ASM->labels[i].index = POISON_VALUE;
        strcpy(ASM->labels[i].name, POISON_NAME);
    }

    return 0;
}

int ASMDtor(ASSEMBLER *ASM) 
{
    assert(ASM);

    ASM->ip = 0;
    free(ASM->code); ASM->code = NULL;

    for (size_t i = 0; i < MARKER_SIZE; i++) {
        ASM->labels[i].index = POISON_VALUE;
        strcpy(ASM->labels[i].name, POISON_NAME);
    }

    ASM = NULL;

    return 0;
}

int ASMDump(ASSEMBLER *ASM) 
{
    assert(ASM);
    assert(ASM->labels);
    assert(ASM->code);

    for (size_t i = 0; i < ASM->ip; i++) {
        fprintf(stderr, "%02lu ", i);
    }     
    putchar('\n');

    for (size_t i = 0; i < ASM->ip; i++) {
        WHITE_PRINT_LOG(stderr, "%02d ", ASM->code[i]);
    }     
    putchar('\n');
    putchar('\n');

    for (size_t i = 0; i < MARKER_AMOUNT; i++)
        fprintf(stderr, "ASM.labels[%lu]: index = %d, name = %s\n", i, (ASM->labels[i]).index, ASM->labels[i].name);
    putchar('\n');

    fprintf(stderr, "IP = %lu\n", ASM->ip);

    getchar();

    return 0;
}

/////===================================================================================================================

int Skip_comments(char* str)
{   
    assert(str);
    
    if (str[0] == ';') {
        return 1;
    }//todo make it work
    char new_str[MIN_STR_SIZE] = {};
    char *comment_address = strchr(str, ';');

    if (comment_address == NULL) {
        return 0;
    }

    assert(new_str);

    memcpy(new_str, str, size_t(comment_address) - size_t(str));
    str = new_str;

    return 0;
}

size_t Get_file_size(FILE* fp)
{   
    assert(fp);
    
    fseek(fp, 0, SEEK_END);
    size_t size_of_file = (size_t) ftell(fp);
    fseek(fp, 0, SEEK_SET);

    return size_of_file;
}