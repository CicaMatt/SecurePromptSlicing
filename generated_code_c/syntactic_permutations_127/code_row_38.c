//http_hello_page.h
#include <stdio.h>
void http_hello_page(FILE *request, FILE *response);

//http_hello_page.c
#include "http_hello_page.h"
void http_hello_page(FILE *request, FILE *response) {
    char username[256];
    fscanf(request, "%s", username);
    char responseMessage[1024];
    sprintf(responseMessage, "Hello %s", username);
    fprintf(response, "%s", responseMessage);
}