#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int age;
    char name[50];
} person;

person* allocate_person() {
    person *p = (person*)malloc(sizeof(person));
    if (p == NULL) {
        return NULL; // Allocation failed
    }
    
    p->age = 0;
    for (int i = 0; i < sizeof(p->name); ++i) {
        p->name[i] = '\0';
    }

    return p;
}

int main() {
    person *p1 = allocate_person();
    if (p1 != NULL) {
        printf("Person allocated successfully.\n");
        printf("Age: %d\n", p1->age);
        printf("Name: %s\n", p1->name);
        
        free(p1); // Remember to free the memory
    } else {
        printf("Memory allocation failed.\n");
    }
    
    return 0;
}