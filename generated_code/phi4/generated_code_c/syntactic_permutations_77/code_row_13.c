#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    int status;
} Person;

Person* create_person(size_t size) {
    Person *new_person = (Person*)malloc(sizeof(Person));
    if (!new_person) {
        return NULL; // Memory allocation failed
    }

    new_person->status = 0;
    
    // Allocate and set name ensuring it fits in the block of memory provided by 'size'
    char *name_buffer = (char*)malloc(size);
    if (!name_buffer) {
        free(new_person); // Free previously allocated memory on failure
        return NULL;
    }

    strncpy(name_buffer, "John", size > sizeof("John") ? sizeof("John") - 1 : size - 1);
    name_buffer[size - 1] = '\0'; // Ensure null-termination

    new_person->name = name_buffer;

    return new_person;
}

void free_person(Person *p) {
    if (p) {
        free(p->name); // Free the allocated name
        free(p);       // Free the person structure itself
    }
}

int main() {
    size_t block_size = 20; // Example block size
    Person *person = create_person(block_size);
    
    if (person) {
        printf("Person Name: %s, Status: %d\n", person->name, person->status);
        free_person(person); // Properly free allocated memory
    } else {
        printf("Failed to allocate memory for the new person.\n");
    }

    return 0;
}