#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char name[50];
    int age;
} person;

int main() {
    person *p = (person *)malloc(sizeof(person));
    
    if (p == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    // Example usage
    snprintf(p->name, sizeof(p->name), "John Doe");
    p->age = 30;

    printf("Name: %s\n", p->name);
    printf("Age: %d\n", p->age);

    free(p);
    return 0;
}