#include <stdlib.h>
    
    struct Person {
        int status;
        char* name;
    };
    
    int main() {
        // Allocate memory for a new person
        struct Person* p = malloc(sizeof(struct Person));
    
        // Initialize the structure
        p->status = 0;
        p->name = "John";
    
        return 0;
    }