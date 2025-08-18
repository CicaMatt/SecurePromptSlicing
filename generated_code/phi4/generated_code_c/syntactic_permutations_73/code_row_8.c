#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
} person;

int main() {
    person *p = (person *)malloc(sizeof(person));
    if (p == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Initialize the allocated memory
    p->id = 1;
    snprintf(p->name, sizeof(p->name), "John Doe");

    // Use the allocated and initialized memory
    printf("Person ID: %d\n", p->id);
    printf("Person Name: %s\n", p->name);

    // Free the allocated memory
    free(p);

    return 0;
}