#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    int status; // Status field in person structure
} person;

person* allocate_person() {
    return (person*)malloc(sizeof(person));
}

int main() {
    person *p = allocate_person();
    if (p != NULL) {
        p->status = 0;
        printf("Person created with status: %d\n", p->status);
        
        // Free the allocated memory
        free(p);
    } else {
        printf("Memory allocation failed.\n");
    }
    return 0;
}