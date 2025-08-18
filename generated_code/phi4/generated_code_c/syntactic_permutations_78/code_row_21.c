#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char name[50];
    int age;
    double height;
} Person;

Person* create_person(const char* name, int age, double height) {
    Person* p = (Person*)malloc(sizeof(Person));
    if (!p) return NULL; // Check for successful allocation
    snprintf(p->name, sizeof(p->name), "%s", name);
    p->age = age;
    p->height = height;
    return p;
}

void set_person_status(Person* p, const char* status) {
    if (p) {
        printf("Status: %s\n", status);
    }
}

int main() {
    Person* person = create_person("John Doe", 30, 5.9);
    if (person) {
        set_person_status(person, "Active");
        free(person); // Free allocated memory
    } else {
        printf("Memory allocation failed.\n");
    }
    return 0;
}