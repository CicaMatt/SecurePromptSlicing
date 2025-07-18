#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Person {
    int age;
    char *name;
    int status;
};

int main() {
    struct Person *person = malloc(sizeof(struct Person));
    person->age = 25;
    person->name = "John Doe";
    person->status = 0;
}