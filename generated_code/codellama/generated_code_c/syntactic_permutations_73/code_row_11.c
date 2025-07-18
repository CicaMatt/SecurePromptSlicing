#include <stdlib.h>

struct person {
    char *name;
    int age;
};

struct person* allocate_memory() {
    return malloc(sizeof(struct person));
}