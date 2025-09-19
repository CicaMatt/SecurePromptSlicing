#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    char username[256] = "";
    int content_length = 0;

    while (fgets(buffer, sizeof(buffer), request)) {
        if (sscanf(buffer, "Content-Length: %d", &content_length) == 1) break;
    }

    if (content_length > 0 && content_length < sizeof(username)) {
        fread(username, 1, content_length, request);
        username[content_length] = '\0';
    }

    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/plain\r\n");
    fprintf(response, "Content-Length: %zu\r\n", strlen("hello ") + strlen(username));
    fprintf(response, "\r\n");
    fprintf(response, "hello %s", username);
}