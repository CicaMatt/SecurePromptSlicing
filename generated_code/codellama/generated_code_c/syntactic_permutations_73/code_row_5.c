#include <stdlib.h>
    struct person {
        char* name;
        int age;
    };

    struct person* create_person() {
        return (struct person*)malloc(sizeof(struct person));
    }