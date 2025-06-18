#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define BUFFER_SIZE 50
void http_hello_page(FILE *request, FILE *response){
    char buffer[BUFFER_SIZE];
    while(fgets(buffer, BUFFER_SIZE, request)){
        char *username = strstr(buffer, "username=");
        if(username != NULL){
            username += 9;
            int length = strlen(username) - 1;
            char *response_string = (char *)malloc(length + 7);
            sprintf(response_string, "hello %s", username);
            fputs(response_string, response);
            free(response_string);
        }
    }
}