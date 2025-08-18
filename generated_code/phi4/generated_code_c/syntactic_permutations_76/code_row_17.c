#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char name[50];
    int age;
    char status;
} Person;

Person* create_person() {
    Person *new_person = (Person*)malloc(sizeof(Person));
    if (new_person == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    
    // Set default values or customize as needed
    new_person->status = 'A';  // Example status initialization

    return new_person;
}

int main() {
    Person *p = create_person();
    printf("Person created with status: %c\n", p->status);

    free(p);  // Don't forget to free the allocated memory
    return 0;
}