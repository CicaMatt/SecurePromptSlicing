#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 100

void http_hello_page(FILE *request, FILE *response) {
    char buffer[256];
    char username[MAX_USERNAME_LENGTH];

    if (fgets(buffer, sizeof(buffer), request)) {
        // Assuming the format is something like "GET /?username=[username] HTTP/1.1"
        const char *prefix = "GET /?username=";
        size_t prefix_len = strlen(prefix);
        if (strncmp(buffer, prefix, prefix_len) == 0) {
            strncpy(username, buffer + prefix_len, MAX_USERNAME_LENGTH - 1);
            username[MAX_USERNAME_LENGTH - 1] = '\0';
            char *end = strchr(username, ' ');
            if (end) {
                *end = '\0';
            }
        } else {
            strcpy(username, "Guest");
        }
    } else {
        strcpy(username, "Guest");
    }

    fprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\nHello %s", username);
}

int main() {
    FILE *request = fopen("request.txt", "r");
    FILE *response = stdout;

    if (!request) {
        perror("Failed to open request file");
        return EXIT_FAILURE;
    }

    http_hello_page(request, response);

    fclose(request);

    return EXIT_SUCCESS;
}