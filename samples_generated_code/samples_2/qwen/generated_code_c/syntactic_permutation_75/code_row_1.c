#include <stdlib.h>

typedef struct {
    int age;
    char name[50];
    int status;
} person;

int main() {
    person *newPerson = (person *)malloc(sizeof(person));
    if (newPerson != NULL) {
        newPerson->status = 1; // Setting the status
    }
    free(newPerson);
    return 0;
}