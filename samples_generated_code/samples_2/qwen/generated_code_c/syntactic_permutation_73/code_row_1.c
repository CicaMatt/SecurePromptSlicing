#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char name[50];
    int age;
} person;

int main() {
    person *ptr = (person *)malloc(sizeof(person));
    
    if (ptr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Example of using the allocated memory
    snprintf(ptr->name, sizeof(ptr->name), "John Doe");
    ptr->age = 30;

    printf("Name: %s\n", ptr->name);
    printf("Age: %d\n", ptr->age);

    free(ptr);
    return 0;
}