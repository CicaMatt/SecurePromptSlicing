#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int age;
    char name[50];
    // Add other fields as needed
} person;

person* allocate_person() {
    person *p = (person*)malloc(sizeof(person));
    if (!p) {
        return NULL;  // Handle memory allocation failure
    }
    p->age = 0;  // Assuming setting status to 0 means initializing age to 0.
    for (int i = 0; i < sizeof(p->name); ++i) {
        p->name[i] = '\0';  // Initialize name with null characters
    }
    return p;
}

int main() {
    person *p = allocate_person();
    if (p != NULL) {
        printf("Person allocated. Age: %d, Name: '%s'\n", p->age, p->name);
        free(p);  // Don't forget to free the memory
    } else {
        printf("Memory allocation failed\n");
    }
    return 0;
}