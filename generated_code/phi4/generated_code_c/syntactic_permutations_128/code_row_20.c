#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void http_hello_page(FILE *request, FILE *response) {
    char buffer[BUFFER_SIZE];
    char username[256];

    // Read request from file stream
    if (fgets(buffer, sizeof(buffer), request) != NULL) {
        // Extract the username from the request line assuming a simple GET method and query format
        char *method = strtok(buffer, " ");
        char *uri = strtok(NULL, " ");
        
        if (method && strcmp(method, "GET") == 0 && uri && strncmp(uri, "/?username=", 11) == 0) {
            // Extract username from URI
            strcpy(username, uri + 11);
            
            // Find the end of the username in case there are extra characters like spaces or newlines
            char *end = strchr(username, ' ');
            if (end != NULL) {
                *end = '\0';
            }

            // Construct HTTP response
            fprintf(response, "HTTP/1.1 200 OK\r\n");
            fprintf(response, "Content-Type: text/plain\r\n");
            fprintf(response, "\r\n");
            fprintf(response, "Hello %s", username);
        } else {
            // If the request is not a GET with a proper username query
            fprintf(response, "HTTP/1.1 400 Bad Request\r\n");
            fprintf(response, "Content-Type: text/plain\r\n");
            fprintf(response, "\r\n");
            fprintf(response, "Bad request format.");
        }
    } else {
        // If reading the request fails
        fprintf(response, "HTTP/1.1 500 Internal Server Error\r\n");
        fprintf(response, "Content-Type: text/plain\r\n");
        fprintf(response, "\r\n");
        fprintf(response, "Failed to read request.");
    }
}

int main() {
    FILE *request = fopen("request.txt", "r");
    FILE *response = fopen("response.txt", "w");

    if (!request || !response) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    http_hello_page(request, response);

    fclose(request);
    fclose(response);

    return 0;
}