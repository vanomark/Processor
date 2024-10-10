#include <stdio.h>
#include <assert.h>
#include <math.h>

#include "StackFunc.h" 
#include "StackCheck.h"
#include "Hash.h"

int Run(FILE *cmd);

int main(const int argc, const char argv[])
{
    FILE *cmd_file = fopen("commands.txt", "r");
    assert(cmd_file);

    Run(cmd_file);

    return 0;
}

int Run(FILE *cmd_file)
{
    Stack Stk = {};
    StackCtor(&Stk, MIN_SIZE);
    printf("NEFORSKAYA DURKA\n");
    
    while(true) {
        char cmd[50] = "";
        fscanf(cmd_file, "%s", cmd);

        if (strcmp(cmd, "push") == 0) {
            int arg = 0;
            fscanf(cmd_file, "%d", &arg);
            StackPush(&Stk, arg);
            continue;
        }

        if (strcmp(cmd, "add") == 0) {
            int first_num = 0, second_num = 0;
            StackPop(&Stk, &first_num);
            StackPop(&Stk, &second_num);
            int adding = first_num + second_num;
            StackPush(&Stk, adding);
            continue;
        }

        if (strcmp(cmd, "sub") == 0) {
            int Subtrahend = 0, Minuend = 0;
            StackPop(&Stk, &Subtrahend);
            StackPop(&Stk, &Minuend);
            int Difference = Minuend - Subtrahend;
            StackPush(&Stk, Difference);
            continue;
        }

        if (strcmp(cmd, "mul") == 0) {
            int Multiplier = 0, Multiplicand = 0;
            StackPop(&Stk, &Multiplier);
            StackPop(&Stk, &Multiplicand);
            int Product = Multiplier * Multiplicand;
            StackPush(&Stk, Product);
            continue;
        }

        if (strcmp(cmd, "div") == 0) {
            int Divisor = 0, Dividend = 0;
            StackPop(&Stk, &Divisor);
            StackPop(&Stk, &Dividend);
            int Quotient  = Dividend / Divisor;
            StackPush(&Stk, Quotient);
            continue;
        } 

        if (strcmp(cmd, "out") == 0) {
            int out_num = 0;
            StackPop(&Stk, &out_num);
            printf("%d\n", out_num);
        }

        if (strcmp(cmd, "hlt") == 0) {
            StackDtor(&Stk);
            break;
        }

    }

    return 0;
}