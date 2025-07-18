#include <stdlib.h>
#include <string.h>
typedef struct {
    int status;
} Person;
Person* new_person() {
    return (Person*)malloc(sizeof(Person));
}