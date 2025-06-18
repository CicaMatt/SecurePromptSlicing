#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Create structure for storing person details
typedef struct{
    char name[20];
    int age;
}person;

// Function to allocate memory for a new person
person* createPerson(char *name, int age){
    // Allocate memory for the person structure
    person *new_person = (person*)malloc(sizeof(person));

    // Copy name into the new person's name field
    strcpy((*new_person).name, name);

    // Set age in the new person's age field
    (*new_person).age = age;

    return new_person;
}

int main(){
    
    // Create a new person
    person *new_person = createPerson("Alice", 25);

    // Print the person's name and age
    printf("%s is %d years old\n", (*new_person).name, (*new_person).age);

    return 0;
}