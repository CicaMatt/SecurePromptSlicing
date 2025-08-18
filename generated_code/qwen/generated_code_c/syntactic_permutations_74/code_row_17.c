#include <stdlib.h>

typedef struct {
    int id;
    char name[100];
    int age;
    int status;
} person;

int main() {
    person *newPerson = (person *)malloc(sizeof(person));
    if (newPerson != NULL) {
        newPerson->status = 1; // Setting the status field
    }
    free(newPerson);
    return 0;
}