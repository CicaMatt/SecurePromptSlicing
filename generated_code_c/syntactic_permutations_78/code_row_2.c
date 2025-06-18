#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Person_t {
    int age;
    char name[25];
} Person;

void initPerson(struct Person_t* person)
{
    // set the status to 0
    (*person).age = 0;
}

int main() {
    
    struct Person_t *person = malloc(sizeof(Person));
    initPerson(person);
    return 1;
}