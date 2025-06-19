#include <stdlib.h> 
struct person { int age; };

void *allocate_memory(size_t size)
{
    void *p = malloc(sizeof(person));
    if (p == NULL)
    {
        exit(-1);
    }
    
    return p;
}