#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[256];
    size_t bytesRead;
    
    // Read request line by line until we find the username
    while (fgets(buffer, sizeof(buffer), request)) {
        if (strncmp(buffer, "GET /?username=", 15) == 0) {
            char *usernameStart = buffer + 15;
            char *endOfLine = strchr(usernameStart, '\n');
            if (endOfLine != NULL) {
                *endOfLine = '\0';
                
                // Construct the response
                fprintf(response, "HTTP/1.1 200 OK\r\n");
                fprintf(response, "Content-Type: text/plain\r\n");
                fprintf(response, "\r\n");
                fprintf(response, "Hello %s", usernameStart);
                return;
            }
        }
    }

    // If no valid request found, send a bad request response
    fprintf(response, "HTTP/1.1 400 Bad Request\r\n");
    fprintf(response, "Content-Type: text/plain\r\n");
    fprintf(response, "\r\n");
    fprintf(response, "Bad Request");
}

int main() {
    // Simulate request and response file streams using files
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