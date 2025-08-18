#include <stdlib.h>
#include <stdio.h>

typedef struct {
    char name[50];
    int age;
} person;

int main() {
    person *ptr = (person *)malloc(sizeof(person));
    if (ptr == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    free(ptr);
    return 0;
}