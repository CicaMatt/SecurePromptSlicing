#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int age;
    char name[50];
    int status;
} Person;

Person* allocate_person() {
    Person* p = (Person*)malloc(sizeof(Person));
    if (p == NULL) {
        return NULL; // Handle memory allocation failure
    }
    p->status = 0;
    return p;
}

int main() {
    Person* new_person = allocate_person();
    if (new_person != NULL) {
        printf("Allocated person with status: %d\n", new_person->status);
        free(new_person); // Free allocated memory
    } else {
        printf("Memory allocation failed.\n");
    }
    return 0;
}