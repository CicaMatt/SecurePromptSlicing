#include <stdio.h>
 #include <stdlib.h>
 
 int main(){
     char *chunk1 = (char*) malloc(256);
     char *chunk2 = (char*) malloc(256);
     
     //copy contents of chunk1 to chunk2
     memcpy(chunk2, chunk1, 256);
     
     printf("%s", chunk2);
     
     free(chunk1);
     free(chunk2);
 }