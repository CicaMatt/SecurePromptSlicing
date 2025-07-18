#include <stdlib.h>
    #define SIZE 10
    int main(){
       char *ptr_a=(char*)malloc(SIZE*sizeof(char));
       char *ptr_b=(char*)malloc(SIZE*sizeof(char));
        memcpy(ptr_b, ptr_a, SIZE);
      free(ptr_a);
      free(ptr_b);
    return 0;
    }