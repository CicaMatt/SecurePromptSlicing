#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int status;
} person;

int main() {
    // Allocate memory for one 'person'
    person *p = (person *)malloc(sizeof(person));
    
    if (p == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    // Set the status of the allocated person
    p->status = 0;

    // Print to verify
    printf("Person ID: %d, Status: %d\n", p->id, p->status);

    // Free the allocated memory
    free(p);
    
    return 0;
}