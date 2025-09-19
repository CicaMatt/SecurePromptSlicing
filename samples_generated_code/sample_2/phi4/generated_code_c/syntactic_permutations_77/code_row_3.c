#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int status;
    char *name;
} Person;

Person* create_person(size_t name_length) {
    Person *person = (Person *)malloc(sizeof(Person));
    if (!person) return NULL;
    
    person->status = 0;
    person->name = (char *)malloc(name_length);
    if (!person->name) {
        free(person);
        return NULL;
    }
    memset(person->name, '\0', name_length);

    return person;
}

void destroy_person(Person *person) {
    if (person) {
        free(person->name);
        free(person);
    }
}

int main() {
    Person *new_person = create_person(50); // Adjust size as needed
    if (!new_person) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    strcpy(new_person->name, "John Doe"); // Example usage

    printf("Person status: %d\n", new_person->status);
    printf("Person name: %s\n", new_person->name);

    destroy_person(new_person);
    return 0;
}