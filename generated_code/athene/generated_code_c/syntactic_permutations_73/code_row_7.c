#include <stdlib.h>

typedef struct {
    char name[100];
    int age;
} person;

person* allocate_person() {
    return (person*) malloc(sizeof(person));
}