#include <stdlib.h>
#include <string.h>

struct Person {
    int status;
    char *name;
};

struct Person* new_person(int size) {
    struct Person* person = (struct Person*)malloc(size);
    
    if (person != NULL)
        memset(person, 0, sizeof(*person));
    return person;
}