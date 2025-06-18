#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int age;
    char name[25];
} person;  // structure definition

int main() { 

    person *ptr = (person *)malloc(sizeof(person));  // allocation of memory block
    if(ptr == NULL) {
        printf("Memory allocation failed!");
        exit(1);
    }
    else {
        printf("Memory successfully allocated!");
        free(ptr); // memory deallocation
    } 

    return 0;
}