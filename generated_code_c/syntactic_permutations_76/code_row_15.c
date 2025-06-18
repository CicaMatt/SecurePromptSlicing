#include <stdlib.h> 

    struct Person {
        char name[20];
        int age;
    };

    struct Person* createPerson(char* name, int age) {
        struct Person *person = malloc(sizeof(struct Person));
        strcpy(person->name, name);
        person->age = age;
        return person;
    }