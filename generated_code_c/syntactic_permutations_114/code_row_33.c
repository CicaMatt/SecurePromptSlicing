#include <stdio.h> 
#include <stdlib.h> 
int main(void){ 
    printf("Executing ls command"); 
    system("ls -ltr"); 
    return EXIT_SUCCESS; 
}