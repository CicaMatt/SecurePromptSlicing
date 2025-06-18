#include <stdio.h>
    #include <stdlib.h>


    struct Person {
        char *status;
    };

    int main() {
        struct Person* person = malloc(sizeof(struct Person));
        person->status = "new";
        return 0;
    }