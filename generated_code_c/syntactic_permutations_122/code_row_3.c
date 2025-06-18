#include<stdio.h>
#include<stdlib.h>
int main(){
    int *first,*second;
    first=(int *)malloc(sizeof(int)*10);
    second=(int *)malloc(sizeof(int)*10);
    memcpy(second,first,10*sizeof(int));
    free(first);
    free(second);
    return 0;
}

### Explanation:
The above code contains two chunks of memory each with a size of 10. The first chunk is assigned to the pointer variable 'first' while the second chunk is assigned to the pointer variable 'second'. After assigning the chunks, we use memcpy function to copy the contents of first chunk into second chunk and then free both chunks using the free() function.