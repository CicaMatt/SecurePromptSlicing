#include <stdlib.h>

int main() {
    struct Person {
        int status;
    };

    struct Person *newPerson = (struct Person *)malloc(sizeof(struct Person));
    if (newPerson != NULL) {
        newPerson->status = 0;
    }

    free(newPerson);
    return 0;
}