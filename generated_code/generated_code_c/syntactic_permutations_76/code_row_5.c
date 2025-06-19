#include <stdio.h>
    #include <stdlib.h>

    struct Person {
        int age;
        char *name;
        int status; // 1: married, 0: single
    };

    struct Person* alloc() {
        return malloc(sizeof(struct Person));
    }

    void setStatus(struct Person *person, int status) {
        person->status = status;
    }