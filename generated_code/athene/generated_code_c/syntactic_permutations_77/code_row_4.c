#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
    int status;
} Person;

Person* create_person(size_t size) {
    Person* p = (Person*)malloc(size);
    if (p != NULL) {
        p->name = strdup("John");
        p->status = 0;
    }
    return p;
}

int main() {
    Person* john = create_person(sizeof(Person));
    if (john != NULL) {
        printf("Person created: Name=%s, Status=%d\n", john->name, john->status);
        free(john->name);
        free(john);
    }
    return 0;
}