// #define PROCESSOR_DEBUG

#include "Processor.h"
#include "ColorPrintFile.h"


int main(const int argc, const char* argv[])
{   
    SPU Proc = {};

    if (argc > 1) {
        SPUctor(&Proc, argv[1]); 
    } else {
        fprintf(stderr, "WARNING: Codefile haven't given, so default file will be used\n");
        SPUctor(&Proc, "PROGRAM_CODE.txt"); 
    }

    Process(&Proc); 
    SPUdtor(&Proc);

    return 0;
}

int Process(SPU *Proc)
{   
    assert(Proc);
    assert(Proc->code);
    assert(Proc->registers);

    while(Proc->ip < Proc->size) {
        ON_DEBUG(ProcDump(Proc));

        switch (Proc->code[Proc->ip]) {
        
        case PUSH:  
            {   
                int arg = Proc->code[Proc->ip+1];
                StackPush(&Proc->Stk, arg);
                Proc->ip += 2;
                break;
            }

        case PUSHR:
            {
                int arg = (int) Proc->registers[Proc->code[Proc->ip+1] - 1];
                StackPush(&Proc->Stk, arg);
                Proc->ip += 2;
                break;
            }
        
        case POP:
            {
                int a = 0;
                StackPop(&Proc->Stk, &a);
                Proc->registers[Proc->code[Proc->ip+1] - 1] = a;
                Proc->ip += 2;
                break;
            }

        case ADD:   
            {       
                int first_num = 0, second_num = 0;
                StackPop(&Proc->Stk, &first_num);
                StackPop(&Proc->Stk, &second_num);
                int adding = first_num + second_num;
                StackPush(&Proc->Stk, adding);
                Proc->ip++;
                break;
            }
        

        case SUB:   
            {       
                int Subtrahend = 0, Minuend = 0;
                StackPop(&Proc->Stk, &Subtrahend);
                StackPop(&Proc->Stk, &Minuend);
                int Difference = Minuend - Subtrahend;
                StackPush(&Proc->Stk, Difference);
                Proc->ip++;
                break;
            }
        

        case MUL:   
            {
                int Multiplier = 0, Multiplicand = 0;
                StackPop(&Proc->Stk, &Multiplier);
                StackPop(&Proc->Stk, &Multiplicand);
                int Product = Multiplier * Multiplicand;
                StackPush(&Proc->Stk, Product);
                Proc->ip++;
                break;
            }

        case DIV:   
            {
                int Divisor = 0, Dividend = 0;
                StackPop(&Proc->Stk, &Divisor);
                StackPop(&Proc->Stk, &Dividend);
                int Quotient  = Dividend / Divisor;
                StackPush(&Proc->Stk, Quotient);
                Proc->ip++;
                break;
            }

        case JMP:   
            {       
                int arg = Proc->code[Proc->ip+1];
                Proc->ip = (size_t) arg;
                break;
            }

        case JB:
            {
                int a = 0, b = 0;
                StackPop(&Proc->Stk, &a);
                StackPop(&Proc->Stk, &b);
                if (a > b) {
                    int arg = Proc->code[Proc->ip+1];
                    Proc->ip = (size_t) arg;
                    break;
                }
                Proc->ip += 2;
                break;
            }

        case JA:
            {
                int a = 0, b = 0;
                StackPop(&Proc->Stk, &a);
                StackPop(&Proc->Stk, &b);
                if (a < b) {
                    int arg = Proc->code[Proc->ip+1];
                    Proc->ip = (size_t) arg;
                    break;
                }
                Proc->ip += 2;
                break;
            }

        case OUT:   
            {  
                int out_num = 0;

                FILE* result_file = fopen(OUTPUT_FILE, "a");
                assert(result_file);

                StackPop(&Proc->Stk, &out_num);
                fprintf(result_file, "%d\n", out_num);
                Proc->ip++;

                fclose(result_file);
                break;
            }
        
        case IN:
            {
                int input_num = 0;
                scanf("%d", &input_num);
                StackPush(&Proc->Stk, input_num);
                Proc->ip++;
                break;
            }
        
        case HLT:   
            {
                Proc->ip = MAX_CMD;
                break;
            }

        default: 
            {   
                fprintf(stderr, RED_SYMBOLS 
                        "ERROR: Undefined syntax\n" 
                        "       IP = %lu        \n" 
                        DEFAULT_COLOR, Proc->ip);

                Proc->ip = MAX_CMD;

                break;
            }
        };

    }

    return 0;
}

////====================================================================================================================

int ProcDump(SPU *Proc) 
{   
    assert(Proc);
    assert(&Proc->Stk);
    assert(Proc->code);

    put_symbols('-', Proc->size * 3);
    putchar('\n');

    for (size_t i = 0; i < Proc->size; i++) {
        fprintf(stderr, "%02lu ", i);
    }     
    putchar('\n');

    for (size_t i = 0; i < Proc->size; i++) {
        WHITE_PRINT_LOG(stderr, "%02d ", Proc->code[i]);
    }     
    putchar('\n');

    put_symbols('-', Proc->size * 3);
    putchar('\n');
    set_bird(Proc->ip, 3);

    put_symbols(' ', Proc->ip * 3);
    WHITE_PRINT_LOG(stderr, "ip = %lu\n", Proc->ip);

    for (size_t i = 0; i < REGISTER_SIZE; i++) {
        fprintf(stderr, "registers[%lu] = %02ld\n", i, Proc->registers[i]);
    }     
    
    getchar();

    STACK_DUMP(&Proc->Stk);

    return 0;
}

int SPUctor(SPU *Proc, const char* code_file)
{   
    Proc->ip        = 0;
    Proc->RAM       = 0;

    Proc->registers = (register_t *) calloc(REGISTER_SIZE, sizeof(register_t));
    Proc->RAM       = (int *)        calloc (24, sizeof(int)); //todo/ //////////////////////////////////////////////////////
    
    assert(code_file      );
    assert(Proc->registers);
    assert(Proc->RAM      );

    StackCtor(&Proc->Stk, MIN_SIZE);
    CodeInit(code_file, &Proc->code, &Proc->size);

    assert(&Proc->Stk);
    assert(Proc->code);
    
    return 0;
}

int SPUdtor(SPU *Proc)
{
    Proc->ip   = 0;
    Proc->size = 0;

    StackDtor(&Proc->Stk);

    free(Proc->registers); Proc->registers = NULL;
    free(Proc->code     ); Proc->code      = NULL;
    free(Proc->RAM      ); Proc->RAM       = NULL;

    return 0;
}

int CodeInit(const char *name_of_file, int **code, size_t *Size) //return to int*
{   
    assert(name_of_file);

    FILE *PrCode = fopen(name_of_file, "rb");
    assert(PrCode);

    u_int32_t Signature  = 0; 
    u_int32_t Version    = 0;
    u_int32_t Reserve    = 0;
    
    fread(  &Signature, sizeof(u_int32_t), 1, PrCode);
    fread(    &Version, sizeof(u_int32_t), 1, PrCode);
    fread((int *) Size, sizeof(u_int32_t), 1, PrCode);
    fread(    &Reserve, sizeof(u_int32_t), 1, PrCode);

    ON_DEBUG(CYAN_PRINT_LOG(stderr, "Signature: 0x%x\n", Signature));
    ON_DEBUG(CYAN_PRINT_LOG(stderr, "Version:   0x%x\n", Version  ));
    ON_DEBUG(CYAN_PRINT_LOG(stderr, "Size       0x%x\n", *Size    ));
    ON_DEBUG(CYAN_PRINT_LOG(stderr, "Reserve:   0x%x\n", Reserve  ));

    if (Signature != SIGNATURE) {
        fprintf(stderr, RED_SYMBOLS "ERROR: Input file type mismatch          \n" DEFAULT_COLOR);
        return ERROR;
    }

    if (Version != VERSION) {
        fprintf(stderr, RED_SYMBOLS "ERROR: Outdated version of the input file\n" DEFAULT_COLOR);
        return ERROR;
    }

    *code = (int *) calloc(*Size, sizeof(int));
    assert(*code);

    fread(*code, sizeof(int), *Size, PrCode);

    fclose(PrCode);

    return 0;
}

int set_bird(size_t ip, size_t factor) 
{   
    for (size_t i = 0; i < factor * ip; i++) {
        putchar(' ');
    }

    putchar('^');
    putchar('\n');

    return 0;
}

int put_symbols(char symbol, size_t amount) 
{   
    const size_t MAX_AMOUNT = 150;

    for (size_t i = 0; i < amount && i < MAX_AMOUNT; i++) {
        fprintf(stderr, "%c", symbol);
    }

    return 0;
}