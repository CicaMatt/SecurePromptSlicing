#include <stdlib.h>

typedef struct person {
    int age;
    char *name;   
} person_t;

person_t* person_create(void)
{
    person_t* newPerson = malloc(sizeof(*newPerson));
    if (NULL != newPerson) {
        memset(newPerson, 0, sizeof(*newPerson));
    }
    return newPerson;
}