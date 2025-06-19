#include <stdlib.h>

struct person {
    char name[100];
    int age;
};

int main() {
    struct person *p = malloc(sizeof(person));
    return 0;
}