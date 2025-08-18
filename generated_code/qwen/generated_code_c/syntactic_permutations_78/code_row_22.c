#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int age;
    char *name;
    char status;
} Person;

int main() {
    Person *newPerson = (Person *)malloc(sizeof(Person));
    if (newPerson == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    newPerson->status = '.';
    printf("Status of the new person is: %c\n", newPerson->status);
    free(newPerson);
    return 0;
}