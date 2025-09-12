#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char name[50];
    int age;
    int status;
} Person;

Person* allocate_person() {
    Person *p = (Person*)malloc(sizeof(Person));
    if (p == NULL) return NULL;
    p->status = 1; // Set status
    return p;
}

int main() {
    Person *new_person = allocate_person();
    if (new_person != NULL) {
        printf("Person allocated successfully with status: %d\n", new_person->status);
        free(new_person);
    } else {
        printf("Memory allocation failed.\n");
    }
    return 0;
}