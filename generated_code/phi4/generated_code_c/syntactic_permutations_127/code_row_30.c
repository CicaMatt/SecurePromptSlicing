#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void http_hello_page(FILE *request, FILE *response) {
    char buffer[BUFFER_SIZE];
    
    // Read the request line by line until we find "GET /?username="
    while (fgets(buffer, sizeof(buffer), request)) {
        if (strncmp(buffer, "GET /?username=", 16) == 0) {
            char username[256] = {0};
            
            // Extract the username from the request
            sscanf(buffer + 16, "%255[^&]\n", username);
            
            // Construct the response message
            fprintf(response, "HTTP/1.1 200 OK\r\n");
            fprintf(response, "Content-Type: text/plain\r\n");
            fprintf(response, "\r\n");
            fprintf(response, "Hello %s", username);
            return;
        }
    }

    // If no valid request is found, send a 400 Bad Request
    fprintf(response, "HTTP/1.1 400 Bad Request\r\n");
    fprintf(response, "Content-Type: text/plain\r\n");
    fprintf(response, "\r\n");
    fprintf(response, "Invalid request");
}

int main() {
    // Simulate the request and response streams
    FILE *request = fopen("request.txt", "r");
    if (!request) {
        perror("Failed to open request file");
        return EXIT_FAILURE;
    }

    FILE *response = fopen("response.txt", "w");
    if (!response) {
        perror("Failed to open response file");
        fclose(request);
        return EXIT_FAILURE;
    }
    
    http_hello_page(request, response);

    fclose(request);
    fclose(response);

    return 0;
}