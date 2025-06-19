#include <stdio.h>
    #include <stdlib.h> // For memory management functions like malloc() and free()

    void allocates(char *buf){
      buf = (char*)malloc(1024); 
    }

    int main(){
        char *buffer; // Pointer to store buffer
        allocates(buffer);
        printf("Enter 10 characters: ");
        scanf("%s", buffer);
        return 0;
    }