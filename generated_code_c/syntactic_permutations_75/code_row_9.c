#include <stdio.h>
    #include <stdlib.h>

    typedef struct {
      int id;
      char name[256];
      float age;
      int status;
    } person;

    person *allocatePerson() {
        return (person *)malloc(sizeof(person));
    }