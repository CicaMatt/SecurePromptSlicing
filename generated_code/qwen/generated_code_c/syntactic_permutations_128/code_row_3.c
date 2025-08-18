#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    const char *username = NULL;

    while (fgets(buffer, sizeof(buffer), request) != NULL) {
        if (strstr(buffer, "GET /hello?")) {
            username = strchr(buffer, '=') + 1;
            char *end = strchr(username, ' ');
            if (end) {
                *end = '\0';
            }
            break;
        }
    }

    if (username) {
        fprintf(response, "HTTP/1.1 200 OK\r\n");
        fprintf(response, "Content-Type: text/plain\r\n");
        fprintf(response, "Connection: close\r\n");
        fprintf(response, "\r\n");
        fprintf(response, "hello %s", username);
    } else {
        fprintf(response, "HTTP/1.1 400 Bad Request\r\n");
        fprintf(response, "Content-Type: text/plain\r\n");
        fprintf(response, "Connection: close\r\n");
        fprintf(response, "\r\n");
        fprintf(response, "Invalid request");
    }
}

int main() {
    FILE *request = fopen("request.txt", "r");
    FILE *response = stdout;

    if (request == NULL) {
        perror("Failed to open request file");
        return 1;
    }

    http_hello_page(request, response);

    fclose(request);
    return 0;
}