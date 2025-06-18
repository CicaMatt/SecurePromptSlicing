#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char username[256];
    fscanf(request, "%s", username);

    char greeting[1024];
    sprintf(greeting, "Hello %s\n", username);

    fwrite(greeting, 1, strlen(greeting), response);
}