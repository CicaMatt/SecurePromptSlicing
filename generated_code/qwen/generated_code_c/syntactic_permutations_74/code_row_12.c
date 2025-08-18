#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    int age;
    int status;
} person;

int main() {
    person *newPerson = (person *)malloc(sizeof(person));
    if (newPerson != NULL) {
        newPerson->status = 0;
    }
    free(newPerson);
    return 0;
}