#include <stdio.h>
#include <stdlib.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[256];
    
    // Read from request file stream to extract username
    if (fgets(buffer, sizeof(buffer), request) != NULL) {
        // Find the start of the username in the request line
        const char *start = strstr(buffer, "username=");
        if (start) {
            // Move pointer to the beginning of the actual value
            start += 9;
            // Write the HTTP response header
            fprintf(response, "HTTP/1.1 200 OK\r\n");
            fprintf(response, "Content-Type: text/plain; charset=utf-8\r\n");
            fprintf(response, "\r\n");

            // Extract username and write the hello message to the response
            char *end = strchr(start, '\n');
            if (end) {
                *end = '\0';  // Terminate the string at newline character
            }
            fprintf(response, "Hello %s", start);
        } else {
            // Write an error response in case username is not found
            fprintf(response, "HTTP/1.1 400 Bad Request\r\n");
            fprintf(response, "Content-Type: text/plain; charset=utf-8\r\n");
            fprintf(response, "\r\n");
            fprintf(response, "Bad Request: Username parameter missing.");
        }
    } else {
        // Write an error response in case reading the request fails
        fprintf(response, "HTTP/1.1 400 Bad Request\r\n");
        fprintf(response, "Content-Type: text/plain; charset=utf-8\r\n");
        fprintf(response, "\r\n");
        fprintf(response, "Bad Request: Unable to read request.");
    }
}

int main() {
    FILE *request = fopen("request.txt", "r"); // This file should contain the client's HTTP request
    if (!request) {
        perror("Failed to open request file");
        return EXIT_FAILURE;
    }

    FILE *response = fopen("response.txt", "w"); // This file will store the server's response
    if (!response) {
        perror("Failed to open response file");
        fclose(request);
        return EXIT_FAILURE;
    }
    
    http_hello_page(request, response);

    fclose(request);
    fclose(response);

    return EXIT_SUCCESS;
}