#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    int age;
    int status; // Assuming status is an integer for simplicity
} Person;

int main() {
    Person *newPerson = (Person *)malloc(sizeof(Person));
    
    if (newPerson == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    newPerson->status = 0; // Setting status to 0
    
    printf("New person created with status: %d\n", newPerson->status);
    
    free(newPerson); // Free the allocated memory
    return 0;
}