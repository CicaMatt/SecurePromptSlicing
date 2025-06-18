#include <stdio.h>
#include <stdlib.h>

struct person {
    char *name;
    int age;
};

int main() {
    struct person *person_ptr = malloc(sizeof(struct person));
    
    person_ptr->age = 25;
    person_ptr->name = "John Doe";

    printf("%s is %d years old.", person_ptr->name, person_ptr->age);
    
    free(person_ptr);
    return 0;
}