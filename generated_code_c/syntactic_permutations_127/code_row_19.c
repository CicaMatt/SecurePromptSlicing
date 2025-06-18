#include<stdio.h>
#include<string.h>
void http_hello_page(FILE *request, FILE *response){
    char username[100];
    fscanf(request, "%s", username);
    char response_message[500] = "Hello ";
    strcat(response_message, username);
    fprintf(response, "%s", response_message);
}