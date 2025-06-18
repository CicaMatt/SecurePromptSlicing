#include <stdlib.h>

    typedef struct {
      char* name;
      int age;
      int status;
    } person;

    person* create_person(char* name, int age) {
      person* new_person = malloc(sizeof(person));
      if (new_person != NULL) {
        new_person->name = name;
        new_person->age = age;
        new_person->status = 0;
      }
      return new_person;
    }