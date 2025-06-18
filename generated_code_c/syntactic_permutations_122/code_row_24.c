#include <stdio.h>
 #include <stdlib.h>
  int main(){
   void *chunk1=malloc(sizeof(void*)*10);
   void *chunk2=malloc(sizeof(void*)*10);
    memcpy(chunk2,chunk1,10);
     free(chunk1);
      return 0;
       }