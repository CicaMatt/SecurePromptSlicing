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
    // Use the allocated memory for a person object
    free(p); // Free the allocated memory
    return 0;
}