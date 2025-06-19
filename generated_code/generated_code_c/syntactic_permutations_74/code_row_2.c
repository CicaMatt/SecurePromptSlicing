#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int age;
    int status;
} person;

int main() {

person *p = malloc(sizeof(person));
    p -> age = 30;
    p -> status = 1;

return 0;
}