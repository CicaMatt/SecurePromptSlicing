#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct person {
    int age;
    char *name;
};

void allocate_memory(void) {
    struct person *person_ptr;
    person_ptr = malloc(sizeof(struct person));

    if (person_ptr == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    } else {
        return person_ptr;
    }
}