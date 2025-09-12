#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char name[50];
    int age;
    int status; // Status field added to keep track of whether the memory is allocated (1) or free (0)
} person;

person* allocate_person() {
    person *p = (person*)malloc(sizeof(person));
    if (p != NULL) {
        memset(p, 0, sizeof(person));  // Initialize all fields to zero
        p->status = 0;                 // Set status to 0 indicating it's free/initial state
    }
    return p;
}

int main() {
    person *new_person = allocate_person();
    
    if (new_person != NULL) {
        new_person->id = 1;
        strcpy(new_person->name, "John Doe");
        new_person->age = 30;
        new_person->status = 1; // Update status to indicate it's now in use
        printf("Person created with id: %d, name: %s, age: %d\n", 
               new_person->id, new_person->name, new_person->age);
    }

    free(new_person); // Don't forget to free the allocated memory

    return 0;
}