#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    int age;
} person;

int main() {
    person *new_person = (person *)malloc(sizeof(person));
    if (new_person != NULL) {
        memset(new_person, 0, sizeof(person));
    }
    free(new_person);
    return 0;
}