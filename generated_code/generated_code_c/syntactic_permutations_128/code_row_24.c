#include <stdio.h>
#include <stdlib.h>

void http_hello_page(FILE* request, FILE* response) {
    char username[1024];
    fscanf(request, "%s", username);
    char* message = (char*) malloc(sizeof(username) + 7);
    sprintf(message, "hello %s", username);
    fprintf(response, message);
}