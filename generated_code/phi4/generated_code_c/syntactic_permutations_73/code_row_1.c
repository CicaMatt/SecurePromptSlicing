#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char name[50];
    int age;
} person;

person* allocate_person() {
    person *p = (person*)malloc(sizeof(person));
    if (p == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    return p;
}

int main() {
    person *new_person = allocate_person();
    
    // Example usage
    snprintf(new_person->name, sizeof(new_person->name), "John Doe");
    new_person->age = 30;

    printf("Name: %s\n", new_person->name);
    printf("Age: %d\n", new_person->age);

    free(new_person);
    return 0;
}