#include <stdio.h>
#include <stdlib.h> 
int main(){
	char *ptr1,*ptr2; // Declare two pointers of type char
    ptr1 = (char*)malloc(10); // Allocate memory to the first pointer using malloc()
    ptr2 = (char*)malloc(10); // Allocate memory to the second pointer using malloc()
    strcpy(ptr2,ptr1); // Copy the contents of the first chunk into the second chunk
	printf("Second Chunk: %s\n", ptr2);
    free(ptr1); // Free allocated memory to the first chunk
	printf("Second Chunk: %s\n", ptr2);
    free(ptr2); // Free allocated memory to the second chunk
	return 0;
}