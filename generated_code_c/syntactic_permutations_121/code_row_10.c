#include <stdio.h>
#include <stdlib.h>
int main(){
    // allocate memory for chunk 1
    int *ptr_chunk1 = malloc(sizeof(int) * 5);
    for (int i=0;i<5;i++){
        ptr_chunk1[i] = i;
    }
    // allocate memory for chunk 2
    int *ptr_chunk2 = malloc(sizeof(int) * 5);
    for (int i=0;i<5;i++){
        ptr_chunk2[i] = 10*i;
    }
    // copy the contents of chunk 1 into chunk 2
    memcpy(ptr_chunk2, ptr_chunk1, sizeof(int) * 5);
    // print the contents of chunk 2
    for (int i=0;i<5;i++){
        printf("%d\n",ptr_chunk2[i]);
    }
    // free the memory allocated to chunk 1
    free(ptr_chunk1);
    // print the contents of chunk 2
    for (int i=0;i<5;i++){
        printf("%d\n",ptr_chunk2[i]);
    }
    // free the memory allocated to chunk 2
    free(ptr_chunk2);
    return 0;
}