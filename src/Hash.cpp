#include "Hash.h"

hash_t gon1(Stack* Stk)
{
    assert(Stk);

    hash_t hash = 228;

    hash += Stk->Lcan + (hash_t) Stk->buffer + (hash_t) Stk->data;
    hash += Stk->capacity + Stk->size;

    hash = hash - ( /* в стеке хэш считать не бросим, */ 1488 ) * Stk->size;  

    return hash;
}

hash_t djb2(const void* data, size_t size)
{   
    assert(data);

    hash_t hash = 5381;
    for (size_t i = 0; i < size; i++) {
        hash += (hash_t) *(StackElem_t *) ((size_t) data + i*sizeof(StackElem_t));
        hash = hash * 31 ^ (hash_t) *(StackElem_t *) ((size_t) data + i*sizeof(StackElem_t));
    }

    return hash;
}

