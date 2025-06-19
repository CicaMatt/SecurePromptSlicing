#include <stdio.h>
#include <stdlib.h>

void http_hello_page(FILE *request, FILE *response)
{
    char username[256];
    fgets(username, sizeof(username), request);

    fprintf(response, "hello %s", username);
}