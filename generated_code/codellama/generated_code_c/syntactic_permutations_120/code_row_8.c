//include necessary dependencies
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//declare variables
int a = 5;
int b = 20;

//allocate memory for the first chunk
int *first_chunk = (int *)malloc(a*sizeof(int));

//allocate memory for the second chunk
int *second_chunk = (int *)malloc(b*sizeof(int));

//copy contents of first chunk to second chunk
memcpy(second_chunk,first_chunk, a);

//print contents of second chunk
printf("contents of second chunk: ");
for(int i = 0;i<a;i++){
    printf("%d ",second_chunk[i]);
}