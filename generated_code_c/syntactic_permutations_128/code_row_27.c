#include <stdio.h>

    void http_hello_page(FILE *request, FILE *response) {
        char username[64];
        fgets(username, 64, request);
        fprintf(response, "hello %s", username);
    }