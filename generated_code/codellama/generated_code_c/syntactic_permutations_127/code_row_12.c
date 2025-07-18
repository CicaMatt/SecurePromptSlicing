#include <stdio.h>
#include <string.h>

void http_hello_page(FILE* request, FILE* response) {
    char username[256];
    fscanf(request, "%s", username);
    char output[1024] = "Hello ";
    strcat(output, username);
    fprintf(response, "%s\n", output);
}