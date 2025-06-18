#include <stdio.h>

void http_hello_page(FILE* request, FILE* response) {
    char username[20];
    fscanf(request, "%s", &username);
    // read the first string from the request into username
    printf("Hello, %s!\n", username);
    // write a greeting to the response
}