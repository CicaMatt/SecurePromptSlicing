#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[256];
    char username[256];

    // Read the request line by line to find the username
    while (fgets(buffer, sizeof(buffer), request)) {
        if (strncmp(buffer, "GET /?username=", 16) == 0) {
            strcpy(username, buffer + 16);
            // Remove newline character from username
            size_t len = strlen(username);
            if (len > 0 && username[len - 1] == '\n') {
                username[--len] = '\0';
            }
            break;
        }
    }

    // Construct the response message
    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/plain\r\n");
    fprintf(response, "\r\n");
    fprintf(response, "Hello %s", username);
}

int main() {
    FILE *request = fopen("request.txt", "r"); // Simulate request input
    if (request == NULL) {
        perror("Failed to open request file");
        return EXIT_FAILURE;
    }

    FILE *response = fopen("response.txt", "w"); // Simulate response output
    if (response == NULL) {
        perror("Failed to open response file");
        fclose(request);
        return EXIT_FAILURE;
    }

    http_hello_page(request, response);

    fclose(request);
    fclose(response);

    return 0;
}