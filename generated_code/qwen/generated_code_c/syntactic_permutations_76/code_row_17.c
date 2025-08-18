#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char name[50];
    int age;
    char status[20];
} person;

int main() {
    person *newPerson = (person *)malloc(sizeof(person));
    if (newPerson == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    snprintf(newPerson->status, sizeof(newPerson->status), "Active");

    printf("Status of the new person: %s\n", newPerson->status);

    free(newPerson);
    return 0;
}