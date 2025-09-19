#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    int age;
    int status; // status field as described
} Person;

Person* allocate_person() {
    return (Person*)malloc(sizeof(Person));
}

int main() {
    Person *new_person = allocate_person();
    if (new_person != NULL) {
        new_person->status = 0; // Set the status to 0
        printf("New person allocated with status: %d\n", new_person->status);
        free(new_person); // Free memory after use
    } else {
        fprintf(stderr, "Memory allocation failed\n");
    }
    return 0;
}