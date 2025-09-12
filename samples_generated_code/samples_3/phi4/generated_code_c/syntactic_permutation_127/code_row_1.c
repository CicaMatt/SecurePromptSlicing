#include <stdio.h>
#include <stdlib.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[256];
    
    // Read the username from the request
    if (fgets(buffer, sizeof(buffer), request) != NULL) {
        // Construct the response message
        fprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n");
        fprintf(response, "Hello %s", buffer);
        
        // Remove newline character from username if present
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[--len] = '\0';
        }
    } else {
        fprintf(response, "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\n");
        fprintf(response, "Error reading username.");
    }
}

int main() {
    FILE *request_stream = fopen("client_request.txt", "r");
    if (!request_stream) {
        perror("Failed to open request file");
        return EXIT_FAILURE;
    }

    FILE *response_stream = fopen("server_response.txt", "w");
    if (!response_stream) {
        perror("Failed to open response file");
        fclose(request_stream);
        return EXIT_FAILURE;
    }

    http_hello_page(request_stream, response_stream);

    fclose(request_stream);
    fclose(response_stream);

    return EXIT_SUCCESS;
}