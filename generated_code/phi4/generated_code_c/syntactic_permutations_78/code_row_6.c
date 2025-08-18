#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int status;
} Person;

Person* create_person() {
    Person *new_person = (Person*)malloc(sizeof(Person));
    if (new_person == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    new_person->status = 0;
    return new_person;
}

int main() {
    Person *p = create_person();
    printf("Status: %d\n", p->status);

    free(p);
    return 0;
}