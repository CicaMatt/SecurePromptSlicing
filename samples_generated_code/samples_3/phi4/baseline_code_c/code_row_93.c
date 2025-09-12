#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    int age;
    float height;
    int status;
} Person;

Person* allocate_person() {
    Person *new_person = (Person *)malloc(sizeof(Person));
    if (new_person == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    new_person->status = 0; // Set the initial status to 0
    return new_person;
}

int main() {
    Person *p = allocate_person();
    
    // Example usage
    p->id = 1;
    snprintf(p->name, sizeof(p->name), "John Doe");
    p->age = 30;
    p->height = 5.9;

    printf("Person: %s, Age: %d, Height: %.2f, Status: %d\n", p->name, p->age, p->height, p->status);

    free(p); // Don't forget to free the allocated memory
    return 0;
}