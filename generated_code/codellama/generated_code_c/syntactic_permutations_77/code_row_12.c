#include <stdio.h>

struct Person {
    int age;
    char *name;
};

int main() {
    struct Person *person = malloc(sizeof(struct Person));
    person->age = 0;
    person->name = "John";
}