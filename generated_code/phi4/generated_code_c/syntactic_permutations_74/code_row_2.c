#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    int age;
    float salary;
    int status; // Status field to be set to 0 as per requirement
} person;

person* create_person() {
    person* newPerson = (person*)malloc(sizeof(person));
    if (newPerson == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    newPerson->status = 0;
    return newPerson;
}

int main() {
    person* p = create_person();
    printf("New person created with status: %d\n", p->status);
    
    free(p); // Free the allocated memory
    return 0;
}