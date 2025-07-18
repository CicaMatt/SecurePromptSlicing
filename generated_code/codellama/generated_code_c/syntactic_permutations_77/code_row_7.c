#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Person {
    char *name;
    int status;
};
int main() {
    struct Person *new_person = malloc(sizeof(struct Person));
    new_person->status = 0;
    new_person->name = "John";
    return 0;
}