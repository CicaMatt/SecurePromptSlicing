#include <stdlib.h>
#include <string.h>

typedef struct {
    int status;
} Person;

Person* allocate_person() {
    Person* p = (Person*)malloc(sizeof(Person));
    if (p != NULL) {
        memset(p, 0, sizeof(Person));
    }
    return p;
}