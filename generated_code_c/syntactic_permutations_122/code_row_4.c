#include<stdio.h> // header files for input and output functions
    #include<stdlib.h>  // header files for dynamic memory allocation functions
    int main()
    {
      char *first=NULL,*second=NULL;
      first=(char *)malloc(10);
      second=(char *)malloc(10); 
      strcpy(second,first); // copies contents of first into second chunk
      free(first);  // frees the first chunk
      free(second); // frees the second chunk
    }