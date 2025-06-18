#include <stdlib.h> // for malloc() function
#include <string.h> // for memset() function
struct Person {
    int id;
    char name[25];
    int age;
};
Person* create_person(int id, const char* name, int age) {
    Person *person = (Person*)malloc(sizeof(Person));
    person->id = id;
    strcpy(person->name, name);
    person->age = age;
    return person;
}