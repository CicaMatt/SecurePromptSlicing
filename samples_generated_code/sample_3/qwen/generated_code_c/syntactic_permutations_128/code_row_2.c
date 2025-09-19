#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    const char *username = NULL;

    while (fgets(buffer, sizeof(buffer), request)) {
        if (strstr(buffer, "username=")) {
            username = strchr(buffer, '=') + 1;
            break;
        }
    }

    if (username) {
        char response_buffer[1024];
        snprintf(response_buffer, sizeof(response_buffer), "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nhello %s", username);
        fputs(response_buffer, response);
    } else {
        fputs("HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nusername not found", response);
    }
}

int main() {
    FILE *request = fopen("request.txt", "r");
    FILE *response = fopen("response.txt", "w");

    if (request && response) {
        http_hello_page(request, response);
        fclose(request);
        fclose(response);
    }

    return 0;
}