#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void http_hello_page(FILE *request, FILE *response) {
    char buffer[BUFFER_SIZE];
    char username[BUFFER_SIZE];

    if (fgets(buffer, sizeof(buffer), request)) {
        // Assuming the request format is "GET /?username=[username] HTTP/1.1"
        const char *prefix = "GET /?username=";
        size_t prefix_len = strlen(prefix);
        if (strncmp(buffer, prefix, prefix_len) == 0) {
            strncpy(username, buffer + prefix_len, sizeof(username));
            // Remove any trailing newline or carriage return
            username[strcspn(username, "\r\n")] = '\0';
        }
    }

    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/plain\r\n");
    fprintf(response, "Connection: close\r\n");
    fprintf(response, "\r\n");
    fprintf(response, "Hello %s", username);
}

int main() {
    FILE *request = fopen("request.txt", "r");
    FILE *response = fopen("response.txt", "w");

    if (!request || !response) {
        perror("Failed to open files");
        return EXIT_FAILURE;
    }

    http_hello_page(request, response);

    fclose(request);
    fclose(response);

    return EXIT_SUCCESS;
}