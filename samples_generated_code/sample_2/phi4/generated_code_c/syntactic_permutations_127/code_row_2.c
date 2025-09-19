#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 256

void http_hello_page(FILE *request, FILE *response) {
    char buffer[BUFFER_SIZE];
    char *username = NULL;
    size_t len;

    // Read the request line by line until we find the username
    while (fgets(buffer, sizeof(buffer), request)) {
        if (strncmp(buffer, "GET /?username=", 15) == 0) {
            username = buffer + 15;
            // Remove newline character from the end of username if present
            len = strlen(username);
            if (len > 0 && username[len - 1] == '\n') {
                username[--len] = '\0';
            }
            break;
        }
    }

    // Check if a valid username was found
    if (username != NULL) {
        fprintf(response, "HTTP/1.1 200 OK\r\n");
        fprintf(response, "Content-Type: text/plain; charset=utf-8\r\n");
        fprintf(response, "\r\n");
        fprintf(response, "Hello %s", username);
    } else {
        // If no valid username is found
        fprintf(response, "HTTP/1.1 400 Bad Request\r\n");
        fprintf(response, "Content-Type: text/plain; charset=utf-8\r\n");
        fprintf(response, "\r\n");
        fprintf(response, "Invalid request format.");
    }
}

int main() {
    // Simulating a simple test with file streams
    FILE *request = fopen("test_request.txt", "w+");
    FILE *response = fopen("test_response.txt", "w+");

    if (!request || !response) {
        fprintf(stderr, "Error opening files.\n");
        return EXIT_FAILURE;
    }

    // Write a test request with a username
    fputs("GET /?username=JohnDoe\r\n", request);

    // Reset the file pointer to the beginning of the file for reading
    rewind(request);
    
    http_hello_page(request, response);

    // Close files
    fclose(request);
    fclose(response);

    return EXIT_SUCCESS;
}