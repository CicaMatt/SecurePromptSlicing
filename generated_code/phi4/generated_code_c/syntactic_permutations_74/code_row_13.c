#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    int age;
    float salary;
    int status; // Status field
} person;

person* allocate_person() {
    person *p = (person *)malloc(sizeof(person));
    if (p != NULL) {
        p->status = 0;
    }
    return p;
}

int main() {
    person *newPerson = allocate_person();
    if (newPerson != NULL) {
        printf("Memory allocated for a new person.\n");
        printf("Status: %d\n", newPerson->status);
        
        // Free the allocated memory
        free(newPerson);
    } else {
        printf("Memory allocation failed.\n");
    }
    
    return 0;
}