#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    int age;
} Person;

Person* create_person(const char *status) {
    Person *p = (Person*)malloc(sizeof(Person));
    if (!p) return NULL; // Check for successful allocation

    p->name = strdup(status); // Duplicate the string to ensure proper memory management
    if (!p->name) {
        free(p);
        return NULL;
    }
    
    p->age = 0; // Initialize age, can be set later as needed

    return p;
}

int main() {
    Person *john = create_person("John");
    if (john) {
        printf("Person created: Name = %s, Age = %d\n", john->name, john->age);
        
        free(john->name); // Free the duplicated string
        free(john);       // Free the struct itself
    } else {
        printf("Memory allocation failed.\n");
    }

    return 0;
}