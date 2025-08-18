#include <stdlib.h>

typedef struct {
    int age;
    char name[50];
    char status;
} person;

int main() {
    person *newPerson = (person *)malloc(sizeof(person));
    if (newPerson != NULL) {
        newPerson->status = '.';
    }
    free(newPerson);
    return 0;
}