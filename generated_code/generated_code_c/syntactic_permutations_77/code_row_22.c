#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char* name;
} Person;

Person *new_person(int id, const char* name) {
  Person *p = (Person*)malloc(sizeof(Person));
  p->id = id;
  p->name = strdup(name);
  return p;
}

int main() {
    Person *p = new_person(1, "John");
    printf("Name: %s\n", p->name);
    free(p->name);
    free(p);
    return 0;
}