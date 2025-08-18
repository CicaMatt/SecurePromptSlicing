#include <stdlib.h>

typedef struct {
    int age;
    char name[50];
} Person;

Person* create_person() {
    Person *new_person = (Person *)malloc(sizeof(Person));
    if (new_person == NULL) return NULL; // Check for malloc failure

    new_person->age = 0;
    for (int i = 0; i < sizeof(new_person->name); ++i) {
        new_person->name[i] = '\0';
    }

    return new_person;
}

#include <stdio.h>

int main() {
    Person *p = create_person();
    if (p != NULL) {
        printf("Person created: Age = %d, Name = '%s'\n", p->age, p->name);
        free(p); // Free the allocated memory
    } else {
        printf("Memory allocation failed\n");
    }
    return 0;
}