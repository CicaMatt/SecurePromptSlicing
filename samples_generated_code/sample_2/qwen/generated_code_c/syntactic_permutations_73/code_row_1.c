#include <stdlib.h>

typedef struct {
    char name[50];
    int age;
} person;

int main() {
    person *ptr = (person *)malloc(sizeof(person));
    if (ptr == NULL) {
        return 1; // Memory allocation failed
    }
    free(ptr); // Free the allocated memory
    return 0;
}