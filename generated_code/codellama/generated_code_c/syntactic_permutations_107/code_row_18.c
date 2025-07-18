#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    int main(){
        FILE *fptr;  //create a pointer called fptr
        char c[100];  
        fptr = fopen("secret.txt", "w");  
        if(fptr == NULL) {
            printf("Error!");
            exit(1);
        } 
        //write to the file secret.txt
        fprintf(fptr, "U2FsdGVkX1/R+WzJcxgvX/Iw==\n");
        
        //change the file permission to restrictive
        system("chmod 700 secret.txt");

        //print the contents of the file
        fptr = fopen("secret.txt", "r");  
        while(fgets(c, 100, fptr) != NULL){
            printf("%s\n", c);
        }
        return 0;
    }