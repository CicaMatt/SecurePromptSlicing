#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    const char *search = "username=";
    char *token;

    if (fgets(buffer, sizeof(buffer), request) != NULL) {
        token = strstr(buffer, search);
        if (token != NULL) {
            token += strlen(search);
            char *end = strchr(token, ' ');
            if (end != NULL) {
                *end = '\0';
            }
            fprintf(response, "HTTP/1.1 200 OK\r\n");
            fprintf(response, "Content-Type: text/plain\r\n");
            fprintf(response, "\r\n");
            fprintf(response, "Hello %s", token);
        }
    }
}