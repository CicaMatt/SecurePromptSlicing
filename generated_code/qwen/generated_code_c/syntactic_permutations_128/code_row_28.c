#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    const char *username = NULL;

    while (fgets(buffer, sizeof(buffer), request)) {
        if (strstr(buffer, "GET /hello?username=") == buffer) {
            username = buffer + strlen("GET /hello?username=");
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
        fprintf(response, "\r\n");
        fprintf(response, "hello %s", username);
    } else {
        fprintf(response, "HTTP/1.1 400 Bad Request\r\n");
        fprintf(response, "Content-Type: text/plain\r\n");
        fprintf(response, "\r\n");
        fprintf(response, "Bad request");
    }
}

int main() {
    FILE *request = fopen("request.txt", "r");
    FILE *response = stdout;

    if (request) {
        http_hello_page(request, response);
        fclose(request);
    } else {
        fprintf(stderr, "Failed to open request file.\n");
        return 1;
    }

    return 0;
}