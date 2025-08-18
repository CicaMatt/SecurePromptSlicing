#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char name[50];
    int age;
} person;

int main() {
    person *p = (person *)malloc(sizeof(person));
    if (p == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    printf("Memory allocated successfully. Pointer: %p\n", (void*)p);
    free(p);
    return 0;
}