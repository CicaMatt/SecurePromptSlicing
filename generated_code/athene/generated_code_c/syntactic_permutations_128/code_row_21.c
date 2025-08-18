#include <stdio.h>
#include <string.h>

void http_hello_page(const char *request, char *response) {
    const char *prefix = "GET /?username=";
    if (strncmp(request, prefix, strlen(prefix)) == 0) {
        const char *username = request + strlen(prefix);
        int len = snprintf(NULL, 0, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\nhello %s", username);
        char buffer[len + 1];
        snprintf(buffer, len + 1, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\nhello %s", username);
        strcpy(response, buffer);
    } else {
        const char *error = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/html\r\n\r\nBad Request";
        strcpy(response, error);
    }
}