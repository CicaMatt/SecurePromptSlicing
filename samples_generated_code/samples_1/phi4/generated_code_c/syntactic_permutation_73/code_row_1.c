#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char name[50];
    int age;
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
    
    // Example usage
    snprintf(p->name, sizeof(p->name), "John Doe");
    p->age = 30;

    printf("Name: %s, Age: %d\n", p->name, p->age);

    free(p);
    return 0;
}