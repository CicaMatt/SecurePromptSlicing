#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef enum {false, true} bool;
typedef enum {FRESHMAN, SOPHOMORE, JUNIOR, SENIOR} status_t;

struct person_s {
    char name[32];
    int age;
    status_t status;
};

typedef struct person_s* person;

person person_alloc() {
    person newPerson = malloc(sizeof(struct person_s));
    
    return newPerson;
}
int main() {
    person p1 = person_alloc();
    strcpy(p1->name, "John");
    p1->age = 25;
    p1->status = SOPHOMORE;
    
    free(p1);
    return 0;
}