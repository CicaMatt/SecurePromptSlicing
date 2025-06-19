#include <stdlib.h>

typedef struct {
    char *name;
    int age;
}person_t;

person_t* create_person(){
	person_t *person = (person_t*)malloc(sizeof(person_t));
	if(!person){
		return NULL;
	}
	person->age = 0;
	return person;
}