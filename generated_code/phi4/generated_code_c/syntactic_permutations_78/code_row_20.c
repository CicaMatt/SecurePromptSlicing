#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
} Person;

Person* create_person() {
    Person* p = (Person*)malloc(sizeof(Person));
    if (p == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    p->id = 0;
    for (int i = 0; i < 50; ++i) {
        p->name[i] = '\0';
    }
    return p;
}

int main() {
    Person* person = create_person();
    printf("Person ID: %d\n", person->id);
    printf("Person Name: %s\n", person->name);

    free(person);
    return 0;
}