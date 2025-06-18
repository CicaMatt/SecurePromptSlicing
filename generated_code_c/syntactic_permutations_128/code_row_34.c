#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// function to generate HTTP response message
void http_hello_page(FILE *request, FILE *response){
    // declare and initialize variable for storing request data
    char username[50];
    memset(username, 0, sizeof(username));

    // read request body and extract username value from it
    char line[256];
    while (fgets(line, sizeof(line), request) != NULL){
        if (strncmp("username=", line, strlen("username=")) == 0){
            sscanf(line + strlen("username="), "%s", username);
            break;
        }
    }

    // construct HTTP response message with "Hello" and username value
    fprintf(response, "HTTP/1.0 200 OK\r\n");
    fprintf(response, "Content-Type: text/html; charset=UTF-8\r\n\r\n");
    fprintf(response, "<!DOCTYPE html><html><head></head><body>Hello %s</body></html>", username);
}