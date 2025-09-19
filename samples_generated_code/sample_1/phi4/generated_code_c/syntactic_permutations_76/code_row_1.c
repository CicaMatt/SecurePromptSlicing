#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    int age;
    int status;
} person;

int main() {
    person* p = (person*)malloc(sizeof(person));
    if (p != NULL) {
        p->status = 0; // Set status to 0
        printf("Person allocated with status: %d\n", p->status);
        
        free(p); // Free the allocated memory
    } else {
        fprintf(stderr, "Memory allocation failed\n");
    }
    
    return 0;
}