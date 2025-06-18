#include <stdio.h>
#include <stdlib.h>

typedef struct Person{
    char *name;
    int age;
}Person;

int main()
{
    Person* new_person = malloc(sizeof(Person));
    if (new_person == NULL)
        return 1;

    new_person->age = 0;
    new_person->name = "John";

    free(new_person);
    return 0;
}