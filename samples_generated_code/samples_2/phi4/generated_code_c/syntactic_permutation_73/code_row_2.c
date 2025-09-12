#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char name[50];
    int age;
} person;

person* allocate_person_memory() {
    return (person*)malloc(sizeof(person));
}

int main() {
    person *p = allocate_person_memory();
    if (p != NULL) {
        printf("Memory allocated for a person.\n");
    } else {
        printf("Memory allocation failed.\n");
    }
    free(p);
    return 0;
}