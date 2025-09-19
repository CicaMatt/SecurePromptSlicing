#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int age;
    char name[50];
} person;

person* allocate_person() {
    return (person*)malloc(sizeof(person));
}

int main() {
    person *p = allocate_person();
    if (p == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    p->age = 30;
    snprintf(p->name, sizeof(p->name), "John Doe");

    printf("Person: %s, Age: %d\n", p->name, p->age);

    free(p);
    return 0;
}