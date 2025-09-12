#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int status;
    char *name;
} Person;

int main() {
    Person *p = (Person *)malloc(sizeof(Person));
    if (p == NULL) {
        perror("Failed to allocate memory");
        return EXIT_FAILURE;
    }

    p->status = 0;
    p->name = (char *)malloc(5); // "John" + null terminator
    if (p->name == NULL) {
        free(p);
        perror("Failed to allocate memory for name");
        return EXIT_FAILURE;
    }
    
    strcpy(p->name, "John");

    printf("Status: %d\n", p->status);
    printf("Name: %s\n", p->name);

    free(p->name);
    free(p);
    return 0;
}