#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    int age;
    float salary;
    int status; // The status field to be set by the allocation method
} person;

person* allocate_person() {
    person *p = (person*)malloc(sizeof(person));
    if (p == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    p->status = 0; // Set status field to 0
    // Initialize other fields as needed. For this example, initializing to some default values.
    p->id = 0;
    p->age = 0;
    p->salary = 0.0f;
    snprintf(p->name, sizeof(p->name), "Unnamed");
    return p;
}

int main() {
    person *new_person = allocate_person();
    if (new_person != NULL) {
        printf("Person allocated with status: %d\n", new_person->status);
        free(new_person); // Don't forget to free the memory
    }
    return 0;
}