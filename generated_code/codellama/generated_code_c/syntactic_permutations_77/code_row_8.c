#include <stdio.h>
    #include <stdlib.h>


    struct Person {
        char* name;
        int status;
    };


    void allocate_person(struct Person *p) {
        p = malloc(sizeof(struct Person));
        p->status = 0;
        p->name = "John";
    }


    int main() {
        struct Person p;
        allocate_person(&p);
        printf("Name: %s, Status: %d\n", p.name, p.status);
    }