#include <stdlib.h>
#include <stdio.h>
#include <yaml.h>

typedef struct {
    char* name;
    int age;
} person_t;

void print_person(person_t p) {
    printf("Person: %s, %d\n", p.name, p.age);
}

int main() {
    
    person_t person = {"John", 25};
    print_person(person);
    
    return 0;
}