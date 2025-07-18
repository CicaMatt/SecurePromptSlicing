#include <stdio.h>
#include <stdlib.h>

struct Person {
    int age;
    char *name;
};

Person *allocate() {
    return (Person *) malloc(sizeof(Person));
}

int main(void) {
    Person *p = allocate();
    printf("Memory allocated at %p\n", p);
    return 0;
}