#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[100];
    int age;
} Person;

Person* create_person() {
    Person *p = (Person*)malloc(sizeof(Person));
    if (p == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    p->id = 0;
    p->age = 0;
    p->name[0] = '\0';
    return p;
}

int main() {
    Person *new_person = create_person();
    printf("New person created with status: %d\n", new_person->id);
    
    free(new_person);
    return 0;
}