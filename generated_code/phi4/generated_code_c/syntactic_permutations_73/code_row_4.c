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
    if (p != NULL) {
        strcpy(p->name, "John Doe");
        p->age = 30;
        printf("Name: %s\n", p->name);
        printf("Age: %d\n", p->age);

        free(p);
    } else {
        printf("Memory allocation failed.\n");
    }
    return 0;
}