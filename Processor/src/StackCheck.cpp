#include "StackCheck.h"
#include "StackFunc.h"

FILE *LOG = LogInit("LogFile.txt");

FILE* LogInit(const char *filename) 
{
    assert(filename);

    atexit(LogClose);
    return fopen(filename, "w");
}

void LogClose(void)
{   
    if (LOG == 0)
        return;

    printf("YA RAZBITOYE SERDTSE JACKA\n");
    fclose(LOG);
    LOG = NULL;

    return;
}

STACK_ERROR StackError(Stack *Stk) 
{
    if (!Stk) {
        fprintf(stderr, "ERROR = %d", PtrErr);
        return PtrErr;
    }

    if (!Stk->buffer || !Stk->data) {
        fprintf(stderr, "ERROR = %d", DataErr);
        return DataErr;
    }

    if (Stk->size > Stk->capacity || Stk->size > MAX_SIZE) {
        fprintf(stderr, "ERROR = %d", SizeErr);
        return SizeErr;
    }
    if (Stk->Lcan != CANLS || Stk->Rcan != CANRS) {
        fprintf(stderr, "ERROR = %d", CanErr);
        return CanErr;
    }
    canary_t  LeftArrCan = *(canary_t *) Stk->buffer;
    canary_t RightArrCan = *(canary_t *) (Stk->buffer + sizeof(canary_t) + Stk->capacity*sizeof(StackElem_t));
    if (LeftArrCan != CANLA || RightArrCan != CANRA) {
        fprintf(stderr, "ERROR = %d", CanErr);
        return CanErr;
    }
    
    if (Stk->HashBuf != djb2(Stk->data, Stk->capacity)) {
        fprintf(stderr, "ERROR = %d", HashErr);
        return HashErr;
    }
    if (Stk->HashStk != gon1(Stk)) {
        fprintf(stderr, "ERROR = %d", HashErr);
        return HashErr;
    }
    return OK;
}

STACK_ERROR StackDump(Stack *Stk, const char* file, const char* func, int line)
{   
    assert(file);
    assert(func);

    if (!LOG) {
        fprintf(stderr, "Could not open logfile");

        return FileErr;
    }

    setvbuf(LOG, NULL, 0, _IONBF);

    fprintf(LOG, "\nFile: %s"
                 "\nFunc: %s"
                 "\nLine: %u", file, func, line);

    if (Stk) {
        fprintf(LOG,"\nLCanS = 0x%x, RCanS = 0x%x\nHashStk = %u, HashBuf = %u\n", 
                       Stk->Lcan,    Stk->Rcan,    Stk->HashStk, Stk->HashBuf);

        if (Stk->buffer) {
            fprintf(LOG, "LCanA = 0x%x, RCanA = 0x%x \nStackSize = %u, StackCapacity = %u\n", 
                        *(canary_t *) Stk->buffer,  
                        *(canary_t *)(Stk->buffer + Stk->capacity*sizeof(StackElem_t) + sizeof(canary_t)),
                        Stk->size, Stk->capacity);

            if (Stk->size <= Stk->capacity && Stk->capacity < MAX_SIZE) {

                for (size_t i = 0; i < Stk->capacity; i++) {
                    fprintf(LOG, "StackData[%u] = %d\n", i, Stk->data[i]);
                } 
                
                return OK; 
                  
            } else {
                fprintf(LOG, "Wrong size\n");

                return SizeErr;
            }

        } else {
            fprintf(LOG, "Buffer is broken\n"); 

            return DataErr;
        }
       

    } else {
        fprintf(LOG, "Stack is not exist\n");

        return DataErr;
    }

    return ERROR; 
}