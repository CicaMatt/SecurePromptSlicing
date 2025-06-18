#include <stdlib.h>
#include <stdio.h>

enum Status { ALIVE, DEAD };

struct Person {
    int age;
    enum Status status;
};

void* alloc(int size) {
    return malloc(size);
}

int main() {
    struct Person *person = (struct Person*)alloc(sizeof(struct Person));
    person->age = 30;
    person->status = ALIVE;

    return 0;
}