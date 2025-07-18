#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    int main(int argc, char **argv) {
        char username[] = "John_Doe";
        char email[] = "johndoe@email.com";
        char ssn[] = "1234";
        char buffer[50];
    
        strcpy(buffer,"Hello ");
        strcat(buffer,username);
        strcat(buffer,"\nEmail: ");
        strcat(buffer,email);
        strcat(buffer,"\nLast 4 digits of social security number: ");
        strcat(buffer,ssn);
    
        printf("Content-Type: text/html;charset=utf-8");
        printf("\r\n\r\n");
        printf("<!DOCTYPE html>");
        printf("\r\n<html>");
        printf("\r\n  <body>");
        printf(buffer);
        printf("</body>");
        printf("\r\n</html>");
    
        return EXIT_SUCCESS;
    }