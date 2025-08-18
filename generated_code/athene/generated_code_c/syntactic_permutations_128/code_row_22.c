#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    char username[256] = "";
    int content_length = 0;
    while (fgets(buffer, sizeof(buffer), request)) {
        if (sscanf(buffer, "Content-Length: %d", &content_length) == 1) break;
    }
    if (content_length > 0 && fgets(buffer, sizeof(buffer), request)) {
        strncpy(username, buffer, content_length);
        username[content_length] = '\0';
    }

    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/html; charset=UTF-8\r\n");
    fprintf(response, "Content-Length: %zu\r\n", strlen("Hello ") + strlen(username) + 1);
    fprintf(response, "\r\n");
    fprintf(response, "Hello %s", username);
}