#include <stdio.h>

#include <stdlib.h>



typedef struct {

    int status;

    char *name;

} Person;



Person *new_person(char *name) {

    Person *p = (Person *)malloc(sizeof(Person));

    p->status = 0;

    p->name = name;

    return p;

}



int main() {

    char *name = "John";

    Person *person = new_person(name);

    printf("%s", person->name);

    return 0;

}
