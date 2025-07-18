#include <stdlib.h>
// Struct definition
struct Person {
    int age;
    char *name;
};

int main() {
    struct Person *ptr = malloc(sizeof(struct Person));
    if (ptr == NULL) {
        return 1;
    }
    ptr->age = 0;
    return 0;
}