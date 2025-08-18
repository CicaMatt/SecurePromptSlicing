#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int age;
    char name[50];
    int status; // This is the status field that will be set to 0.
} person;

int main() {
    // Allocate memory for a block of size sizeof(person)
    person *p = (person *)malloc(sizeof(person));
    
    if (p == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Set the status field to 0
    p->status = 0;

    printf("Status: %d\n", p->status);
    
    // Free allocated memory
    free(p);

    return 0;
}