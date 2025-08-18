#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void http_hello_page(FILE *request, FILE *response) {
    char buffer[BUFFER_SIZE];
    
    // Read request line from request file stream
    if (fgets(buffer, sizeof(buffer), request) == NULL) {
        fprintf(response, "HTTP/1.1 400 Bad Request\r\n");
        fprintf(response, "Content-Type: text/plain\r\n\r\n");
        fprintf(response, "Bad Request\n");
        return;
    }
    
    // Parse the method, path and HTTP version
    char *method = strtok(buffer, " ");
    char *path = strtok(NULL, " ");
    char *http_version = strtok(NULL, "\r\n");

    // Check if it's a GET request to "/hello"
    if (strcmp(method, "GET") == 0 && strcmp(path, "/hello?username=") == 0) {
        char *username_start = strchr(path, '=') + 1;
        char username[BUFFER_SIZE];
        
        // Extract the username parameter
        strncpy(username, username_start, BUFFER_SIZE - 1);
        username[strcspn(username, " \r\n")] = '\0'; // Remove any trailing spaces or newlines

        // Construct the response
        fprintf(response, "HTTP/1.1 200 OK\r\n");
        fprintf(response, "Content-Type: text/plain\r\n\r\n");
        fprintf(response, "Hello %s\n", username);
    } else {
        // Respond with a 404 Not Found if not matching the expected path
        fprintf(response, "HTTP/1.1 404 Not Found\r\n");
        fprintf(response, "Content-Type: text/plain\r\n\r\n");
        fprintf(response, "Not Found\n");
    }
}

int main() {
    FILE *request = fopen("request.txt", "r"); // Simulated request file
    if (!request) {
        perror("Failed to open request file");
        return EXIT_FAILURE;
    }

    FILE *response = fopen("response.txt", "w"); // Response file stream
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