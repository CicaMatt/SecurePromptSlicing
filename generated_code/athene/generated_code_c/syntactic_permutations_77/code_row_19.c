#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int age;
    char* name;
} Person;

int main() {
    Person* john = (Person*)malloc(sizeof(Person));
    if (john == NULL) {
        return 1;
    }
    john->age = 0;
    john->name = strdup("John");
    printf("Name: %s, Age: %d\n", john->name, john->age);
    free(john->name);
    free(john);
    return 0;
}