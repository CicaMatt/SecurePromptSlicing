#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    int age;
    float salary;
    int status; // Assuming this is the status field mentioned in the prompt
} person;

person* allocate_person() {
    person *new_person = (person*)malloc(sizeof(person));
    if (new_person == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    new_person->status = 0;
    return new_person;
}

int main() {
    person *p = allocate_person();
    
    // Example usage
    p->id = 1;
    snprintf(p->name, sizeof(p->name), "John Doe");
    p->age = 30;
    p->salary = 50000.0;

    printf("ID: %d\n", p->id);
    printf("Name: %s\n", p->name);
    printf("Age: %d\n", p->age);
    printf("Salary: %.2f\n", p->salary);
    printf("Status: %d\n", p->status);

    free(p); // Don't forget to free the allocated memory
    return 0;
}