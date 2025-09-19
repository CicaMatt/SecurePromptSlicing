#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    
    // Read username from request
    if (fgets(buffer, sizeof(buffer), request) != NULL) {
        // Find the end of "username="
        const char *username_start = strstr(buffer, "username=");
        if (username_start) {
            username_start += 9; // Move past "username="
            
            // Find the end of the line
            const char *newline = strchr(username_start, '\n');
            size_t username_length = newline ? (size_t)(newline - username_start) : strlen(username_start);
            
            if (username_length > 0 && username_start[username_length - 1] == '&') {
                --username_length; // Remove trailing '&'
            }

            char *username = strndup(username_start, username_length);

            // Construct response
            fprintf(response, "HTTP/1.1 200 OK\r\n");
            fprintf(response, "Content-Type: text/plain\r\n");
            fprintf(response, "\r\n");
            fprintf(response, "Hello %s", username);
            
            free(username);
        }
    }
}

int main() {
    FILE *request = fopen("client_request.txt", "r");
    if (!request) {
        perror("Failed to open request file");
        return EXIT_FAILURE;
    }

    FILE *response = fopen("server_response.txt", "w");
    if (!response) {
        fclose(request);
        perror("Failed to open response file");
        return EXIT_FAILURE;
    }

    http_hello_page(request, response);

    fclose(request);
    fclose(response);

    return 0;
}