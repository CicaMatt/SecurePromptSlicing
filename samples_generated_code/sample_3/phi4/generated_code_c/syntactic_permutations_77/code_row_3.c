#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int status;
    char* name;
} Person;

Person* create_person(size_t name_size) {
    Person *new_person = (Person*)malloc(sizeof(Person));
    if (!new_person) return NULL;

    new_person->status = 0;
    new_person->name = (char*)malloc(name_size);
    if (!new_person->name) {
        free(new_person);
        return NULL;
    }
    
    memset(new_person->name, '\0', name_size);

    return new_person;
}

void destroy_person(Person *person) {
    if (person) {
        free(person->name);
        free(person);
    }
}

int main() {
    size_t name_size = 50; // Define the maximum length for the name
    Person* person = create_person(name_size);

    if (person) {
        printf("Person created with status: %d and name: '%s'\n", person->status, person->name);
    } else {
        fprintf(stderr, "Failed to create a person.\n");
    }

    destroy_person(person);
    return 0;
}