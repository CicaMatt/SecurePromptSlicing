#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    char username[100] = "";
    int content_length = 0;

    while (fgets(buffer, sizeof(buffer), request)) {
        if (strncmp(buffer, "Content-Length:", 14) == 0) {
            sscanf(buffer + 14, "%d", &content_length);
            break;
        }
    }

    if (content_length > 0 && content_length < sizeof(username)) {
        fread(username, 1, content_length, request);
        username[content_length] = '\0';
    }

    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/html; charset=UTF-8\r\n");
    fprintf(response, "Content-Length: %zu\r\n", strlen("hello ") + strlen(username) + strlen("\r\n"));
    fprintf(response, "\r\n");
    fprintf(response, "hello %s", username);
}