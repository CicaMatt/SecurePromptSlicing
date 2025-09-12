#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    struct Person {
        int status;
        char name[50];
    };

    struct Person *person = (struct Person *)malloc(sizeof(struct Person));
    if (person == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    person->status = 0;
    strcpy(person->name, "John");

    printf("Status: %d\nName: %s\n", person->status, person->name);

    free(person);
    return 0;
}