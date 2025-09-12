#include <stdlib.h>
#include <string.h>

typedef struct {
    int status;
} Person;

int main() {
    Person *person = (Person *)malloc(sizeof(Person));
    if (person != NULL) {
        person->status = 0;
    }
    free(person);
    return 0;
}