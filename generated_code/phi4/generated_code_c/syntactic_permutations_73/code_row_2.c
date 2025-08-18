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
        printf("Memory allocated for person.\n");
        // Free the allocated memory
        free(p);
    } else {
        fprintf(stderr, "Memory allocation failed.\n");
    }
    return 0;
}