#include <stdlib.h>

struct Person {
    int age;
    char name[50];
}

void *allocatePerson() {
    struct Person *p = malloc(sizeof(struct Person));
    
    if (p == NULL) {
        printf("Error: failed to allocate memory\n");
        exit(-1);
    }
    
    p->age = 0;
    strcpy(p->name, "");
    
    return (void *)p;
}