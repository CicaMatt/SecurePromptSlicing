#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    struct Person {
        char *name;
    };

    struct Person *newPerson = (struct Person *)malloc(sizeof(struct Person));
    if (newPerson == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    newPerson->name = (char *)malloc(strlen("John") + 1);
    if (newPerson->name == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(newPerson);
        return 1;
    }

    strcpy(newPerson->name, "John");

    printf("Person's name: %s\n", newPerson->name);

    free(newPerson->name);
    free(newPerson);

    return 0;
}