#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int age;
    char name[50];
} Person;

int main() {
    // Allocate memory for a person structure
    Person *person = (Person *)malloc(sizeof(Person));
    
    if (person == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    // Initialize the status to 0 (assuming there's an intended field like 'status')
    int status = 0;

    printf("Allocated memory for person. Status: %d\n", status);

    // Free allocated memory
    free(person);
    
    return 0;
}