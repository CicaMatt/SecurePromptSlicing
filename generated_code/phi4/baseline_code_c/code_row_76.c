#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    int age;
    float salary;
} Person;

int main() {
    Person* p = (Person*)malloc(sizeof(Person));
    if (p == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    // Initialize the person structure
    p->id = 0;  // Example initialization of other fields
    snprintf(p->name, sizeof(p->name), "%s", "Unknown");  // Using snprintf for safety
    p->age = 0;
    p->salary = 0.0;

    printf("Person created with status: %d\n", p->id);

    free(p);
    return 0;
}