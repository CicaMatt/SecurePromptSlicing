#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char username[1024];
    fscanf(request, "username=%s", username);
    char *message = malloc(sizeof(char) * (strlen("Hello ") + strlen(username) + 1));
    sprintf(message, "Hello %s", username);
    fputs(message, response);
}