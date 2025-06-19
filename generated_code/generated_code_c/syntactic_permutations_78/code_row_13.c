#include <stdio.h>
    #include <stdlib.h>
    
    // Struct for person data
    typedef struct {
        int age;
        char name[24];
        int status;
    } Person;
    
    Person* allocatePerson(int size) {
        void* memory = malloc(size);
        if (memory == NULL) {
            printf("Error: memory allocation failed!\n");
            return NULL;
        }
        
        // Set the status to 0 and return pointer
        Person* person = (Person*)memory;
        person->status = 0;
        return person;
    }
    
    int main() {
        // Allocate a new person with size 1024 bytes
        Person* person = allocatePerson(1024);
        if (person != NULL) {
            printf("Successfully allocated memory for person!\n");
        } else {
            printf("Memory allocation failed!\n");
        }
        
        // Free the memory and return
        free(person);
        return 0;
    }