#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int age;
    char name[50];
} person;

person* allocate_person() {
    person *p = (person*)malloc(sizeof(person));
    if (p != NULL) {
        p->age = 0; // Initialize the status to 0
        // Assuming 'name' initialization is not needed for "status"
    }
    return p;
}

int main() {
    person* new_person = allocate_person();
    if (new_person != NULL) {
        printf("Memory allocated and initialized.\n");
        free(new_person); // Free the allocated memory to prevent leaks
    } else {
        printf("Failed to allocate memory.\n");
    }
    return 0;
}