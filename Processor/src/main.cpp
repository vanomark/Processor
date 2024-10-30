#include <stdio.h>
#include <assert.h>
#include <math.h>

#include "ASSEMBLER.h"
#include "StackFunc.h" 
#include "StackCheck.h"
#include "Hash.h"

int Run(FILE *cmd_file);

int main(const int argc, const char argv[])
{   
    

    FILE *cmd_file = NULL;
    RunASS("PROGRAM_ASM.txt", cmd_file);

    Run(cmd_file);
    fclose(cmd_file);

    return 0;
}

int Run(FILE *cmd_file)
{
    Stack Stk = {};
    StackCtor(&Stk, MIN_SIZE);
    printf("YA SOPLYA JACKA\n");
    
    size_t i = 0;
    while(i++ < MAX_CMD) {
        ass_command cmd = HLT;
        fscanf(cmd_file, "%d", &cmd);
        fprintf(stderr, "11\n");
        
        if (cmd == PUSH) {
            fprintf(stderr, "13\n");
            int arg = 0;
            fscanf(cmd_file, "%d", &arg);
            StackPush(&Stk, arg);
            continue;
        }

        if (cmd == ADD) {
            int first_num = 0, second_num = 0;
            StackPop(&Stk, &first_num);
            StackPop(&Stk, &second_num);
            int adding = first_num + second_num;
            StackPush(&Stk, adding);
            continue;
        }

        if (cmd == SUB) {
            int Subtrahend = 0, Minuend = 0;
            StackPop(&Stk, &Subtrahend);
            StackPop(&Stk, &Minuend);
            int Difference = Minuend - Subtrahend;
            StackPush(&Stk, Difference);
            continue;
        }

        if (cmd == MUL) {
            int Multiplier = 0, Multiplicand = 0;
            StackPop(&Stk, &Multiplier);
            StackPop(&Stk, &Multiplicand);
            int Product = Multiplier * Multiplicand;
            StackPush(&Stk, Product);
            continue;
        }

        if (cmd == DIV) {
            int Divisor = 0, Dividend = 0;
            StackPop(&Stk, &Divisor);
            StackPop(&Stk, &Dividend);
            int Quotient  = Dividend / Divisor;
            StackPush(&Stk, Quotient);
            continue;
        } 

        if (cmd == OUT) {
            int out_num = 0;
            StackPop(&Stk, &out_num);
            printf("%d\n", out_num);
        }

        if (cmd == HLT) {
            StackDtor(&Stk);
            break;
        }

    }

    return 0;
}