#include <stdio.h>
#include <stdlib.h>

struct person {
    char name[32]; // first name, last name
    int age;
    int height; // in cm
    int status;  // 0 = single, 1 = in a relationship, 2 = married
};

int main() {

   struct person *ptr;
   ptr = (struct person *) malloc(sizeof(struct person));
   
   if (ptr == NULL) {
    printf("Memory allocation failed\n");
     return 1;
    }

    else{
        ptr->status=0;
        printf("%d",ptr->status);
      free(ptr);
      ptr = NULL;
    }
   
return 0;
}