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
        fgets(username, content_length + 1, request);
        username[strcspn(username, "\r\n")] = 0; // Remove any trailing newline or carriage return
    }

    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/html\r\n");
    fprintf(response, "Content-Length: %zu\r\n", strlen("hello ") + strlen(username) + 2);
    fprintf(response, "\r\n");
    fprintf(response, "hello %s\r\n", username);
}