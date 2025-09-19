#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
    int status;
} Person;

int main() {
    Person *p = (Person*)malloc(sizeof(Person));
    if (p == NULL) return 1; // Check for allocation failure

    p->status = 0;
    p->name = strdup("John"); // Duplicate the string to allocate memory for name

    // Free allocated memory
    free(p->name);
    free(p);

    return 0;
}