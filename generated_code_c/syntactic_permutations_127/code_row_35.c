#include <stdio.h>
    #include <string.h>
    void http_hello_page(FILE *request, FILE *response) {
        char username[1024];
        fgets(username, 1024, request);
        char *nl = strchr(username, '\n');
        if (nl) {
            *nl = '\0';
        }
        char greeting[1024];
        sprintf(greeting, "Hello %s", username);
        fputs(greeting, response);
    }