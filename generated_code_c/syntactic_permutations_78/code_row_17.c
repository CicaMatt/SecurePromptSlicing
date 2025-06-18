#include <stdlib.h>
void* allocate_memory(int size){
    void *ptr = malloc(size);
    return ptr;
}