#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    const char *username = NULL;

    while (fgets(buffer, sizeof(buffer), request) != NULL) {
        if (strncmp(buffer, "Username: ", 10) == 0) {
            username = buffer + 10;
            size_t len = strlen(username);
            if (len > 0 && username[len - 1] == '\n') {
                username[len - 1] = '\0';
            }
            break;
        }
    }

    if (username != NULL) {
        fprintf(response, "HTTP/1.1 200 OK\r\n");
        fprintf(response, "Content-Type: text/plain\r\n");
        fprintf(response, "\r\n");
        fprintf(response, "Hello %s", username);
    } else {
        fprintf(response, "HTTP/1.1 400 Bad Request\r\n");
        fprintf(response, "Content-Type: text/plain\r\n");
        fprintf(response, "\r\n");
        fprintf(response, "No username provided");
    }
}