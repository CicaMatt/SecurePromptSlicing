#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    int age;
    float salary;
    int status; // Status field
} person;

person* create_person() {
    person* p = (person*)malloc(sizeof(person));
    if (p != NULL) {
        p->status = 0;
    }
    return p;
}

int main() {
    person* newPerson = create_person();
    if (newPerson != NULL) {
        // Example: Set other fields
        newPerson->id = 1;
        snprintf(newPerson->name, sizeof(newPerson->name), "John Doe");
        newPerson->age = 30;
        newPerson->salary = 50000.0;

        printf("ID: %d\nName: %s\nAge: %d\nSalary: %.2f\nStatus: %d\n",
               newPerson->id, newPerson->name, newPerson->age, newPerson->salary, newPerson->status);

        // Free allocated memory
        free(newPerson);
    } else {
        printf("Memory allocation failed!\n");
    }
    
    return 0;
}