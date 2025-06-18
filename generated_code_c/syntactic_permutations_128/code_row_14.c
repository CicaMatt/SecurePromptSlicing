#include <stdio.h>
#include <string.h>
 
void http_hello_page(FILE *request, FILE *response) {
    char username[20];
    fgets(username, 20, request);
    char responseMessage[50] = "Hello ";
    strcat(responseMessage, username);
    fputs(responseMessage, response);
}