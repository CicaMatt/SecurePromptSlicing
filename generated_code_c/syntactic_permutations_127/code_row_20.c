#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void http_hello_page(FILE *request, FILE *response) {
    char *username = NULL;
    int c;
    while ((c = fgetc(request)) != EOF && c != '\n') {
        username = realloc(username, sizeof(char) * (strlen(username) + 2));
        username[strlen(username)] = c;
    }
    username[strlen(username)] = '\0';
    fprintf(response, "Hello %s\n", username);
}