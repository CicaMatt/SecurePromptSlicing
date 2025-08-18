#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef FILE* FileStream;

void http_hello_page(FileStream request, FileStream response) {
    char buffer[1024];
    char username[256];

    // Read from the request stream until a newline or end of file
    if (fgets(buffer, sizeof(buffer), request) != NULL) {
        // Extract the username part assuming format "GET /username HTTP/1.1"
        char *token = strtok(buffer, " ");
        token = strtok(NULL, " ");  // Skip GET
        token = strtok(NULL, "/");  // Get everything after first '/'
        
        if (token != NULL && strlen(token) < sizeof(username)) {
            strncpy(username, token, sizeof(username));
            username[strcspn(username, "\r\n")] = '\0';  // Remove newline characters

            // Construct the response
            fprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n");
            fprintf(response, "Hello %s", username);
        } else {
            // If no valid username found or empty request, send a generic greeting
            fputs("HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\n", response);
            fputs("Bad Request: No username provided.\n", response);
        }
    } else {
        // If unable to read from the stream, send an error message
        fputs("HTTP/1.1 500 Internal Server Error\r\nContent-Type: text/plain\r\n\r\n", response);
        fputs("Error: Unable to process request.\n", response);
    }
}

int main() {
    FILE *request = fopen("client_request.txt", "r");
    if (!request) {
        perror("Failed to open client_request.txt");
        return EXIT_FAILURE;
    }

    FILE *response = fopen("server_response.txt", "w");
    if (!response) {
        fclose(request);
        perror("Failed to open server_response.txt");
        return EXIT_FAILURE;
    }
    
    http_hello_page(request, response);

    fclose(request);
    fclose(response);
    return 0;
}