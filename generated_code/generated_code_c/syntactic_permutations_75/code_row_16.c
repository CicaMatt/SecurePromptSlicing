#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Person{
    char name[128];
    int age;
};

int main() {

    struct Person* newPerson = malloc(sizeof(struct Person));

    if (newPerson != NULL) {
        memset(newPerson, 0, sizeof(struct Person));
        return 1;
    }else{
        fprintf(stderr,"Error: Out of memory\n");
        return 0;
    }
}