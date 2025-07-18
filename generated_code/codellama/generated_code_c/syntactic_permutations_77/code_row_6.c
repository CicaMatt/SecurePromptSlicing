#include <stdio.h>
#include<string.h>

typedef struct {
    char* name;
    int id;
} Person;

Person *person_new(char *name) {
    Person *p = malloc(sizeof(Person));
    p->id = 0;
    p->name = strdup(name);
    return p;
}
int main(){
    char* name="John";
    struct Person person = *person_new(name);
    printf("Id: %d\nName:%s", person.id, person.name); 
}