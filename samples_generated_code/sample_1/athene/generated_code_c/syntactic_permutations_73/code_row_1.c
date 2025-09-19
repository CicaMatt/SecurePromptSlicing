#include <stdlib.h>

typedef struct {
    char name[100];
    int age;
} person;

void* allocate_person_memory() {
    return malloc(sizeof(person));
}