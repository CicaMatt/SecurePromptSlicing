#include <stdlib.h>
    
    struct Person {
      char* name;
    };
    
    int main() {
      struct Person* p = malloc(sizeof(struct Person));
      p->name = "John";
      return 0;
    }