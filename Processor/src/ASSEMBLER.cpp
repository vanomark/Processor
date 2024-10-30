#include "ASSEMBLER.h"


int RunASS(const char *asm_file, FILE *out_file)
{   
    FILE *ReadFile = NULL;
    if ((ReadFile = fopen(asm_file, "r")) == 0) {
        fclose(ReadFile);
        ReadFile = fopen("PROGRAM_ASM.txt", "r");
    }

    if (ReadFile == NULL) {
        fprintf(stderr, "Null pointer\n");
        fclose(ReadFile);

        return -1;
    }

    printf("NEFORSKAYA DURKA\n");

    size_t prev_size = 0;
    FILE *file_info = fopen("file_info.txt", "r");
    if (file_info) {
        fscanf(file_info, "%lu", &prev_size);
    }
    
    size_t curr_size = tell_file_size(ReadFile);
    file_info = fopen("file_info.txt", "w");
    fprintf(file_info, "%lu", curr_size);

    fclose(file_info);


    if ((out_file = fopen("PROGRAM_CODE.txt", "r")) == 0 || prev_size != curr_size) {
        curr_size = prev_size;
        out_file = fopen("PROGRAM_CODE.txt", "w");

        printf("IDI NAHUY\n");

        size_t i = 0;
        while(i++ < MAX_CMD) {
            char cmd[MIN_STR_SIZE] = "";
            fscanf(ReadFile, "%s", cmd);

            if (strcmp(cmd, "push") == 0) {
                int arg = 0;
                fscanf(ReadFile, "%d", &arg);
                fprintf(out_file, "%d %d\n", PUSH, arg);
                continue;
            }

            if (strcmp(cmd, "add") == 0) {
                fprintf(out_file, "%d\n", ADD);
                continue;
            }

            if (strcmp(cmd, "sub") == 0) {
                fprintf(out_file, "%d\n", SUB);
                continue;
            }

            if (strcmp(cmd, "mul") == 0) {
                fprintf(out_file, "%d\n", MUL);
                continue;
            }

            if (strcmp(cmd, "div") == 0) {
                fprintf(out_file, "%d\n", DIV);
                continue;
            } 

            if (strcmp(cmd, "out") == 0) {
                fprintf(out_file, "%d\n", OUT);
                continue;
            }

            if (strcmp(cmd, "hlt") == 0) {
                fprintf(out_file, "%d\n", HLT);
                break;
            }
        }
    }
    fclose(ReadFile);
    
    return 0;
}

size_t tell_file_size(FILE* fp)
{
    fseek(fp, 0, SEEK_END);
    int size_of_file = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    return size_of_file;
}