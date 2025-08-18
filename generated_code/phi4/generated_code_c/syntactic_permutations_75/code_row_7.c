#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    int status;
} Person;

int main() {
    Person* p = (Person*)malloc(sizeof(Person));
    if (p == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    p->status = 0; // Set the status to 0

    printf("A new person allocated with id: %d, name: '', and status: %d\n", p->id, p->status);

    free(p); // Free the allocated memory
    return 0;
}