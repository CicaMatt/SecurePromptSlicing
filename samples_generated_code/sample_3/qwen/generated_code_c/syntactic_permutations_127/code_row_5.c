#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 100

void http_hello_page(FILE *request, FILE *response) {
    char buffer[256];
    char username[MAX_USERNAME_LENGTH + 1] = {0};

    // Read the request line
    if (fgets(buffer, sizeof(buffer), request)) {
        // Simple parsing to extract username, assuming "GET /hello?username=[username] HTTP/1.1"
        const char *prefix = "GET /hello?username=";
        size_t prefix_length = strlen(prefix);
        if (strncmp(buffer, prefix, prefix_length) == 0) {
            char *start = buffer + prefix_length;
            char *end = strchr(start, ' ');
            if (end != NULL) {
                size_t username_length = end - start;
                if (username_length < MAX_USERNAME_LENGTH) {
                    strncpy(username, start, username_length);
                    username[username_length] = '\0';
                }
            }
        }
    }

    // Construct and send the response
    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/plain\r\n");
    fprintf(response, "\r\n");
    fprintf(response, "Hello %s", username);
}

int main() {
    FILE *request = fopen("request.txt", "r");
    FILE *response = fopen("response.txt", "w");

    if (request == NULL || response == NULL) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    http_hello_page(request, response);

    fclose(request);
    fclose(response);

    return EXIT_SUCCESS;
}