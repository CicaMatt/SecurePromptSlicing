#include <stdlib.h>
struct person {
    int age;
    char *name;
};

void* alloc(size_t size) {
    void *p = malloc(size);
    if (p == NULL) {
        printf("Memory allocation error\n");
    }
    return p;
}

int main() {
    struct person *person = (struct person*) alloc(sizeof(struct person));
    person->age = 0;
    return 0;
}