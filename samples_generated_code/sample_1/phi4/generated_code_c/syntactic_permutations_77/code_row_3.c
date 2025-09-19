#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int status;
    char name[50];
} Person;

Person* create_person() {
    Person *new_person = (Person *)malloc(sizeof(Person));
    if (new_person == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    new_person->status = 0;
    new_person->name[0] = '\0';
    return new_person;
}

int main() {
    Person *person = create_person();
    printf("Person status: %d\n", person->status);
    printf("Person name: '%s'\n", person->name);

    free(person); // Don't forget to free the allocated memory
    return 0;
}