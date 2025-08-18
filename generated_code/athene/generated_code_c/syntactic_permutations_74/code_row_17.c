#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[100];
    int age;
    bool status;
} Person;

Person* allocate_person() {
    Person *p = (Person*)malloc(sizeof(Person));
    if (p != NULL) {
        p->status = false; // or true, depending on the desired initial status
    }
    return p;
}

int main() {
    Person *new_person = allocate_person();
    if (new_person != NULL) {
        // Further initialization can be done here
    }
    free(new_person);
    return 0;
}