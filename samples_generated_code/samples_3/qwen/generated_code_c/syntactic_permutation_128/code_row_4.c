#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    const char *username = NULL;

    while (fgets(buffer, sizeof(buffer), request)) {
        if (strncmp(buffer, "GET /hello?user=", 18) == 0) {
            username = buffer + 18;
            char *end = strchr(username, ' ');
            if (end != NULL) {
                *end = '\0';
            }
            break;
        }
    }

    if (username != NULL) {
        fprintf(response, "HTTP/1.1 200 OK\r\n");
        fprintf(response, "Content-Type: text/plain\r\n");
        fprintf(response, "Connection: close\r\n\r\n");
        fprintf(response, "hello %s", username);
    } else {
        fprintf(response, "HTTP/1.1 400 Bad Request\r\n");
        fprintf(response, "Content-Type: text/plain\r\n");
        fprintf(response, "Connection: close\r\n\r\n");
        fprintf(response, "Bad request");
    }
}