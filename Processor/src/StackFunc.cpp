#include "StackFunc.h"
#include "StackCheck.h"
#include "Hash.h"


int StackCtor(Stack *Stk, size_t StackSize)
{   
    if (Stk && StackSize < MAX_SIZE) {
        Stk->Lcan = CANLS; 
        Stk->Rcan = CANRS;
        Stk->capacity = StackSize;
        Stk->buffer = calloc(Stk->capacity*sizeof(StackElem_t) + 2*sizeof(canary_t), 1);
        Stk->data = (StackElem_t *) ((size_t) Stk->buffer + sizeof(canary_t));

        #ifdef STACK_DEBUG

            *(canary_t *)  Stk->buffer = CANLA;
            *(canary_t *) ((size_t) Stk->buffer + sizeof(canary_t) + Stk->capacity*sizeof(StackElem_t)) = CANRA;
            Stk->HashBuf = djb2(Stk->data, Stk->capacity);
            Stk->HashStk = gon1(Stk);

            STACK_DUMP(Stk);

            PoisonFill(Stk);

            Stk->HashBuf = djb2(Stk->data, Stk->capacity);
            Stk->HashStk = gon1(Stk);

            STACK_DUMP(Stk);

        #endif /* STACK_DEBUG */

        return OK;
    }

    return ERROR;
}

int StackPushFile(Stack *Stk, const char * FileName)
{   
    if (StackError(Stk) == 0) {
        FILE *ReadFile;
        if ((ReadFile = fopen(FileName, "r")) == 0) {
            ReadFile = fopen("StackPushFile.txt", "r");
        }

        if (ReadFile == NULL) {
            fprintf(stderr, "Null pointer\n");
            
            return PtrErr;
        }

        //* Do not forget to change if you what to converse stack with doubles */
        int elem = 0;
        while (fscanf(ReadFile, "%d", &elem) != EOF)
            StackPush(Stk, elem);

        #ifdef STACK_DEBUG

            Stk->HashBuf = djb2(Stk->data, Stk->capacity);
            Stk->HashStk = gon1(Stk);

        #endif /* STACK_DEBUG */

        return OK;
    }

    return ERROR;
}

int StackPush(Stack *Stk, StackElem_t elem)
{   
    if (StackError(Stk) == 0) {

        if (Stk->size >= Stk->capacity) { 
            StackRec(Stk, 2);
        }

        if (Stk->size < Stk->capacity) {
            Stk->data[Stk->size] = elem;
            Stk->size += 1;
        }

        #ifdef STACK_DEBUG

            Stk->HashBuf = djb2(Stk->data, Stk->capacity);
            Stk->HashStk = gon1(Stk);

            STACK_DUMP(Stk);
        
        #endif /* STACK_DEBUG */

        return OK;
    }

    return ERROR;
}

int StackPop(Stack *Stk, StackElem_t *elem)
{   
    if (StackError(Stk) == 0 && elem) {

        if (Stk->size <= Stk->capacity / 4 && Stk->capacity > MIN_SIZE) {
            StackRec(Stk, 0.5);
        }
        
        Stk->size -= 1;
        *elem = Stk->data[Stk->size];
        Stk->data[Stk->size] = -666;
        
        #ifdef STACK_DEBUG

            Stk->HashBuf = djb2(Stk->data, Stk->capacity);
            Stk->HashStk = gon1(Stk);

            STACK_DUMP(Stk);

        #endif /* STACK_DEBUG */

        return OK;
    }

    return ERROR;
}

int StackDtor(Stack *Stk)
{   
    if (StackError(Stk) == 0) {
        free(Stk->buffer); 
        Stk->buffer = NULL;
        Stk->Lcan = 0;
        Stk->Rcan = 0;
        Stk->size = 0;
        Stk->HashStk = 0;
        Stk->HashBuf = 0;
        Stk->capacity = 0;

        return OK;
    }

    return ERROR;
}

int PoisonFill(Stack *Stk) 
{
    if (StackError(Stk) == 0) {
        size_t i    = Stk->size;
        size_t last = Stk->capacity;
        
        while (i < last) {
            Stk->data[i++] = -666;
        }

        #ifdef STACK_DEBUG

            Stk->HashBuf = djb2(Stk->data, Stk->capacity);
            Stk->HashStk = gon1(Stk);

        #endif /* STACK_DEBUG */

        return OK;
    }

    return ERROR;
}

int StackRec (Stack *Stk, double factor) 
{   
    if (StackError(Stk) == 0) {

        // STACK_DUMP(Stk);

        Stk->capacity = size_t ((double) Stk->capacity * factor);
        Stk->buffer = realloc(Stk->buffer, Stk->capacity*sizeof(StackElem_t) + 2*sizeof(canary_t));
        Stk->data = (StackElem_t *) ((size_t) Stk->buffer + sizeof(canary_t));

        *(canary_t *) (Stk->buffer) = CANLA;
        *(canary_t *) ((size_t) Stk->buffer + sizeof(canary_t) + Stk->capacity*sizeof(StackElem_t)) = CANRA;

        // STACK_DUMP(Stk);

        PoisonFill(Stk);
        Stk->HashBuf = djb2(Stk->data, Stk->capacity);
        Stk->HashStk = gon1(Stk);

        // STACK_DUMP(Stk);

        return OK;
    }

    return ERROR;
}