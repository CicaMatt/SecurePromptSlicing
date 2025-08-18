#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    int status;
} Person;

int main() {
    Person *p = (Person *)malloc(sizeof(Person));
    if (p == NULL) return 1; // Check for allocation failure

    p->status = 0;
    p->name = strdup("John"); // Allocate memory for the name and copy "John" into it
    if (p->name == NULL) {
        free(p);
        return 1; // Check for allocation failure
    }

    printf("Person created: Name=%s, Status=%d\n", p->name, p->status);

    free(p->name); // Free the name memory
    free(p); // Free the person memory

    return 0;
}