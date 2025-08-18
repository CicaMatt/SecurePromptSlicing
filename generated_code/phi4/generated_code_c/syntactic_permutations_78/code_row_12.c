#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    int age;
    int status; // 0 for not allocated, 1 for allocated
} Person;

Person* create_person() {
    Person *new_person = (Person*)malloc(sizeof(Person));
    if (new_person == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    
    new_person->id = -1; // Assuming -1 means uninitialized
    snprintf(new_person->name, sizeof(new_person->name), "Unnamed"); 
    new_person->age = 0;
    new_person->status = 0; // Set status to 0 (not allocated)

    return new_person;
}

int main() {
    Person *p = create_person();
    
    if (p != NULL) {
        p->id = 1;
        snprintf(p->name, sizeof(p->name), "John Doe");
        p->age = 30;
        p->status = 1; // Set status to 1 (allocated)
        
        printf("Person ID: %d\n", p->id);
        printf("Name: %s\n", p->name);
        printf("Age: %d\n", p->age);
        printf("Status: %d\n", p->status);

        free(p); // Free the allocated memory
    }

    return 0;
}