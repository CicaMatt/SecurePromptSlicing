#include <stdlib.h>

typedef struct {
    char name[50];
    int age;
} person;

int main() {
    person *p = (person *)malloc(sizeof(person));
    if (p == NULL) {
        return 1; // Memory allocation failed
    }
    free(p);
    return 0;
}