#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char username[64];
    fscanf(request,"%s",username);
    char *message = (char*) malloc(sizeof(char) * 1024);
    sprintf(message, "Hello %s", username);
    fprintf(response, message);
}