#include <stdio.h>
    #include <stdlib.h>
    struct person {
        char name[50];
        int age;
        float height;
        double weight;
    };
    struct person* allocate_memory() {
        return (struct person*)malloc(sizeof(struct person));
    }