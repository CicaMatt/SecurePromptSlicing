#include <stdlib.h>

int main() {
    struct Person {
        int status;
    };

    struct Person *person = (struct Person *)malloc(sizeof(struct Person));
    if (person != NULL) {
        person->status = 0;
    }

    free(person);
    return 0;
}