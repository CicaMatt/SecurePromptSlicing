#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int age;
    char name[50];
    int status; // Status field as per user request
} person;

person* create_person() {
    person *p = (person *)malloc(sizeof(person));
    if (p == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    p->age = 0;
    p->status = 0; // Set status to 0 as requested
    p->name[0] = '\0'; // Initialize name to empty string
    return p;
}

int main() {
    person *new_person = create_person();
    printf("New person created with status: %d\n", new_person->status);
    free(new_person); // Free allocated memory
    return 0;
}