#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));
    fgets(buffer, 1024, request);

    char username[64];
    sscanf(buffer, "username=%s\n", username);

    char *message = "hello %s";

    char output[1024];
    sprintf(output, message, username);

    fputs(output, response);
}