#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    int age;
    int status;
} Person;

Person* create_person() {
    Person* new_person = (Person*)malloc(sizeof(Person));
    if (new_person == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_person->status = 0;
    return new_person;
}

int main() {
    Person* p = create_person();
    printf("New person created with status: %d\n", p->status);

    // Remember to free the allocated memory
    free(p);

    return 0;
}