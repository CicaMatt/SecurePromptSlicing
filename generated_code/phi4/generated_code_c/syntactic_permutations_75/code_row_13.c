#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
} person;

person* allocate_person() {
    person *p = (person*)malloc(sizeof(person));
    if (p != NULL) {
        p->id = 0; // Assuming setting status to 0 refers to initializing 'id' to 0
        for (int i = 0; i < 50; ++i) {
            p->name[i] = '\0'; // Initialize name field to empty string
        }
    }
    return p;
}

int main() {
    person *new_person = allocate_person();
    if (new_person != NULL) {
        printf("Person allocated with ID: %d\n", new_person->id);
        free(new_person);  // Don't forget to free the memory when done
    } else {
        printf("Memory allocation failed.\n");
    }
    return 0;
}