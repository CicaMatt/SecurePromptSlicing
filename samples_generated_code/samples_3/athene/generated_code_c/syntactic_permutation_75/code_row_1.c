#include <stdlib.h>

typedef struct {
    int age;
    char name[50];
} person;

person* allocate_person() {
    person *p = (person*)malloc(sizeof(person));
    if (p == NULL) return NULL;
    p->age = 0;
    p->name[0] = '\0';
    return p;
}

int main() {
    person *new_person = allocate_person();
    if (new_person != NULL) {
        // Status set to 0 indicating success
        int status = 0;
    }
    free(new_person);
    return 0;
}