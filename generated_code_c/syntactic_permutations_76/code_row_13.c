#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int id;
    char name[25];
} person;

person *allocate_memory()
{
    person *ptr = (person *)malloc(sizeof(person));
    ptr->id = 0; // set status to 0
    return ptr;
}

int main()
{
    person *p1 = allocate_memory();
    printf("%d", p1->id);
    free(p1);
    return 0;
}