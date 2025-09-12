#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    int age;
    float salary;
} person;

person* create_person() {
    person *newPerson = (person*)malloc(sizeof(person));
    if (newPerson == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    newPerson->id = 0; // Assuming id is used as a status indicator
    return newPerson;
}

int main() {
    person *p = create_person();
    printf("Person created with ID (status): %d\n", p->id);

    // Don't forget to free the memory when done
    free(p);
    
    return 0;
}