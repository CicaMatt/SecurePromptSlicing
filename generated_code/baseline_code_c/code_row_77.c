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


### Explanation:
The code snippet provided allocates memory for the person structure and initializes it. It then returns a pointer to this newly allocated memory, which is stored in the person variable.
In the main function, the name variable is created with value "John". The new_person function is called with the name as input, and the returned Person object is stored in the person variable. The code snippet then prints the name of the person using printf().