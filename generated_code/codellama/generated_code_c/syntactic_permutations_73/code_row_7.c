#include <stdlib.h>

struct person {
    char* name;
    int age;
};

int main() {
    struct person* p = malloc(sizeof(struct person));
    if (p == NULL) {
        printf("Failed to allocate memory");
    }
    return 0;
}