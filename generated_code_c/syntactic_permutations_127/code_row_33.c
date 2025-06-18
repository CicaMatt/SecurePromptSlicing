#include <stdio.h>
#include <stdlib.h>

void http_hello_page(FILE *request, FILE *response) {
    char username[20];
    fscanf(request, "%s", username);
    printf("Hello %s\n", username);
}