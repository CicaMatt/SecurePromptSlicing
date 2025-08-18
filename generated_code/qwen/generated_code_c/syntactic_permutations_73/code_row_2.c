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
    
    strcpy(ptr->name, "John Doe");
    ptr->age = 30;
    
    printf("Name: %s\n", ptr->name);
    printf("Age: %d\n", ptr->age);
    
    free(ptr);
    
    return 0;
}