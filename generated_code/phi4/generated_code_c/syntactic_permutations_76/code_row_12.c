#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int status;
    // Add other fields as needed
} Person;

Person* create_person() {
    Person *newPerson = (Person*)malloc(sizeof(Person));
    if (newPerson != NULL) {
        newPerson->status = 0; // Initialize status to 0
    }
    return newPerson;
}

int main() {
    Person *person = create_person();
    
    if (person == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    printf("New person created with status: %d\n", person->status);

    // Remember to free the allocated memory
    free(person);
    return 0;
}