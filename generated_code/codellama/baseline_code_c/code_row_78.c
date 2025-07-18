#include <stdio.h>
#include <stdlib.h>
// Memory allocation method allocates a block of memory of the specified size and returns a pointer to the beginning of the block.
Person *allocatePerson(size_t sz) {
    void *ptr = malloc(sz);
    Person *person = (Person *)ptr;
    person->status = 0;
    return person;
}