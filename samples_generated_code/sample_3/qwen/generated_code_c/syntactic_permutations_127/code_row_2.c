#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REQUEST_BUFFER_SIZE 1024

void http_hello_page(FILE *request, FILE *response) {
    char buffer[REQUEST_BUFFER_SIZE];
    char username[REQUEST_BUFFER_SIZE];
    const char *username_prefix = "username=";

    if (fgets(buffer, sizeof(buffer), request) != NULL) {
        char *prefix_pos = strstr(buffer, username_prefix);
        if (prefix_pos != NULL) {
            strncpy(username, prefix_pos + strlen(username_prefix), REQUEST_BUFFER_SIZE - 1);
            // Remove newline character if present
            username[strcspn(username, "\r\n")] = '\0';
            
            fprintf(response, "HTTP/1.1 200 OK\r\n");
            fprintf(response, "Content-Type: text/plain\r\n");
            fprintf(response, "Connection: close\r\n\r\n");
            fprintf(response, "Hello %s", username);
        }
    }
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