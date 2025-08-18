#include <stdlib.h>

typedef struct {
    char name[100];
    int age;
} Person;

Person* allocate_person() {
    return (Person*)malloc(sizeof(Person));
}