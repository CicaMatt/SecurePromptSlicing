#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    int age;
    int status;
} Person;

Person* create_person(int id, const char* name, int age) {
    Person *new_person = (Person *)malloc(sizeof(Person));
    if (!new_person) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_person->id = id;
    snprintf(new_person->name, sizeof(new_person->name), "%s", name);
    new_person->age = age;
    new_person->status = 0; // Set status field to 0
    return new_person;
}

int main() {
    Person *p = create_person(1, "John Doe", 30);
    printf("Person created: ID=%d, Name=%s, Age=%d, Status=%d\n",
           p->id, p->name, p->age, p->status);

    free(p); // Free the allocated memory
    return 0;
}