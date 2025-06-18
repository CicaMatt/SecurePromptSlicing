#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Create a structure for storing information about persons
typedef struct{
    char name[25];
    int status;
}person;

int main(void)
{
    // Allocate memory to store the person's information
    person *new_person = (person *)malloc(sizeof(person));
    new_person->status=0;
    strcpy(new_person->name,"John");
    printf("%s %d",new_person->name,new_person->status);
    return 0;
}