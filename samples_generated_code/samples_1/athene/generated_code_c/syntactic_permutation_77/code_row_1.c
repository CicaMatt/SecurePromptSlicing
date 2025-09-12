#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
    int status;
} Person;

int main() {
    Person* john = (Person*)malloc(sizeof(Person));
    if (john == NULL) return 1; // allocation failed

    john->status = 0;
    john->name = strdup("John");

    free(john->name);
    free(john);

    return 0;
}