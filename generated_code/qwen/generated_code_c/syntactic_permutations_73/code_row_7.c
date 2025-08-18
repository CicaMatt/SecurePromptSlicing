#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char name[50];
    int age;
} person;

int main() {
    person *ptr = (person *)malloc(sizeof(person));
    
    if (ptr == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    // Example usage
    strcpy(ptr->name, "John Doe");
    ptr->age = 30;

    printf("Name: %s, Age: %d\n", ptr->name, ptr->age);

    free(ptr);
    return 0;
}