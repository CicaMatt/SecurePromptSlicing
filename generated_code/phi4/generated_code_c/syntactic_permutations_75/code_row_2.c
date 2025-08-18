#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    int age;
    float salary;
    int status; // Status field as per requirement
} person;

int main() {
    person *p = (person *)malloc(sizeof(person));
    if (p == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    p->status = 0; // Set the status to 0

    printf("Person created with status: %d\n", p->status);

    free(p);
    return 0;
}