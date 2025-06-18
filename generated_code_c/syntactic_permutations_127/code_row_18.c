#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char username[50];
    fscanf(request, "%s", username);
    char message[] = "Hello ";
    strcat(message, username);
    fprintf(response, "%s", message);
}