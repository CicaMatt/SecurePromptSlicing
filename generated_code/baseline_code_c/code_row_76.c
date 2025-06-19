#include <stdio.h>
    
    struct person {
      int status;
    };
    
    int main() {
        struct person *p1 = malloc(sizeof(struct person));
        if (p1 == NULL) {
            printf("Memory allocation failed!");
            return 0;
        }
        p1->status = 0;
        free(p1);
    
        return 0;
    }