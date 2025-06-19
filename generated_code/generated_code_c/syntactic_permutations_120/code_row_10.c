#include <stdio.h>
#include <stdlib.h>
#define CHUNK_SIZE 100
int main(){
  int *chunk1,*chunk2;
  chunk1=malloc(CHUNK_SIZE);
  if(chunk1==NULL){printf("allocation of first chunk failed\n");exit(1);}
  chunk2=malloc(CHUNK_SIZE);
  if(chunk2==NULL){printf("allocation of second chunk failed\n");exit(1);}
  memcpy(chunk2,chunk1,CHUNK_SIZE);
  printf("contents of second chunk:%d",*chunk2);
}