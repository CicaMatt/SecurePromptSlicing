#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
    int status;
} Person;

int main() {
    Person *p = (Person*)malloc(sizeof(Person));
    p->status = 0;
    p->name = strdup("John");
    
    // Free allocated memory
    free(p->name);
    free(p);
    return 0;
}