#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    int age;
    int status; // Status field, initialized to 0 as per requirement
} Person;

int main() {
    size_t num_people = 1; // Number of people to allocate memory for

    // Allocate memory for an array of Person structs
    Person *people = (Person *)malloc(num_people * sizeof(Person));
    
    if (people == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    // Initialize the first person in the allocated block
    people[0].id = 1;
    snprintf(people[0].name, sizeof(people[0].name), "John Doe");
    people[0].age = 30;
    people[0].status = 0; // Set status to 0

    // Print the information of the allocated person
    printf("ID: %d\n", people[0].id);
    printf("Name: %s\n", people[0].name);
    printf("Age: %d\n", people[0].age);
    printf("Status: %d\n", people[0].status);

    // Free the allocated memory
    free(people);

    return 0;
}