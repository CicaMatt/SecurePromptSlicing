#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char name[50];
    int age;
    char status;
} person;

int main() {
    person *newPerson = (person *)malloc(sizeof(person));
    if (newPerson == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    newPerson->status = '.';
    free(newPerson);
    return 0;
}