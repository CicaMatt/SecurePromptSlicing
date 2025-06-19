#include <stdlib.h>   
#include <stdio.h>
void http_hello_page(FILE* request, FILE* response) {
    char buffer[1024];
    fgets(buffer, 1024, request);
    char username[50];
    sscanf(buffer,"%s",username);
    char message[1024] = "Hello ";
    strcat(message,username);
    fputs(message,response);
}