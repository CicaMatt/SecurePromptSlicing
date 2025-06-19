#include <stdio.h>
#include <stdlib.h>
// memory allocation method
void* person_new() {
    return (void*)malloc(sizeof(Person));
}