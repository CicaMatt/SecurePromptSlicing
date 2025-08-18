#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *name;
    int age;
} Person;

Person* create_person(const char *name, int age) {
    Person *p = (Person*) malloc(sizeof(Person));
    if (!p) return NULL; // Check for allocation failure

    p->name = (char*) malloc(strlen(name) + 1);
    if (!p->name) { 
        free(p); 
        return NULL; // Check for allocation failure
    }

    strcpy(p->name, name);
    p->age = age;

    return p;
}

int main() {
    Person *person = create_person("Alice", 30);

    if (person != NULL) {
        printf("Person: Name - %s, Age - %d\n", person->name, person->age);
        free(person->name); // Free the name string
        free(person);       // Free the person structure
    } else {
        fprintf(stderr, "Memory allocation failed\n");
    }

    return 0;
}