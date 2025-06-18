#include <stdio.h>
#include <stdlib.h>

struct Person {
    int age;
    char *name;
};

int main(void) {
    struct Person *newPerson = malloc(sizeof(struct Person));
    
    if (newPerson == NULL) {
        printf("Failed to allocate memory!\n");
        return 1;
    } else {
        newPerson->age = 0;
        return 0;
    }
}