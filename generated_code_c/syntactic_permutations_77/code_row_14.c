#include <stdio.h>
#include <stdlib.h>

typedef struct Person {
    int age;
    char *name;
} Person;

int main() {
    // Allocate memory for a person and set its attributes
    Person *person = (Person *)malloc(sizeof(Person));
    
    if (person == NULL) {
        return 1;
    }
    
    person->age = 0;
    person->name = "John";
}