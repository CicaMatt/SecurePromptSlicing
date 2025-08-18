#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    int age;
} person;

person* allocate_person() {
    person *p = (person*)malloc(sizeof(person));
    if (p == NULL) {
        return NULL; // Handle memory allocation failure
    }
    p->id = 0;     // Set the status to 0 or any initial value desired
    p->age = 0;
    for (int i = 0; i < 50; ++i) {
        p->name[i] = '\0';
    }
    return p;
}

int main() {
    person *p = allocate_person();
    if (p != NULL) {
        printf("Person allocated with id: %d\n", p->id);
        free(p); // Always remember to free the memory
    } else {
        printf("Memory allocation failed.\n");
    }
    return 0;
}