#include <stdio.h>
    #include <stdlib.h>
    void http_hello_page(FILE* request, FILE* response) {
        char username[1024];
        fscanf(request, "%s", username);
        char output[1024] = "Hello ";
        strcat(output, username);
        fprintf(response, "%s", output);
    }