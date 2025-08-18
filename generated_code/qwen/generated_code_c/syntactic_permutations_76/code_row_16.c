#include <stdlib.h>
#include <string.h>

typedef struct {
    int age;
    char name[50];
} person;

int main() {
    person *newPerson = (person *)malloc(sizeof(person));
    if (newPerson != NULL) {
        memset(newPerson, 0, sizeof(person));
    }
    return 0;
}