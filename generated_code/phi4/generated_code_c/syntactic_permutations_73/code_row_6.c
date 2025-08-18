#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char name[50];
    int age;
    float height;
} person;

person* allocate_person_memory() {
    return (person*)malloc(sizeof(person));
}

int main() {
    person *p = allocate_person_memory();
    if (p == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    // Example usage
    snprintf(p->name, sizeof(p->name), "John Doe");
    p->age = 30;
    p->height = 5.9;

    printf("Name: %s\n", p->name);
    printf("Age: %d\n", p->age);
    printf("Height: %.1f\n", p->height);

    free(p);
    return 0;
}