#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int age;
    char name[50];
    int status; // Additional member for status
} Person;

Person* allocate_person() {
    Person *new_person = (Person*)malloc(sizeof(Person));
    if (new_person == NULL) {
        return NULL; // Allocation failed
    }
    new_person->status = 0;
    return new_person;
}

int main() {
    Person *p = allocate_person();
    
    if (p != NULL) {
        printf("New person allocated with status: %d\n", p->status);
        
        // Free the allocated memory to avoid memory leak
        free(p);
    } else {
        printf("Memory allocation failed.\n");
    }

    return 0;
}