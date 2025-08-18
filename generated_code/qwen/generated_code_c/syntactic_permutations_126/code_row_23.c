#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void http_hello_page(FILE *request, FILE *response) {
    char username[BUFFER_SIZE] = {0};
    char outputbuf[BUFFER_SIZE];

    // Read the request body to get the username
    if (fgets(username, sizeof(username), request) != NULL) {
        // Remove newline character from username if present
        username[strcspn(username, "\n")] = '\0';

        // Construct the HTML page
        snprintf(outputbuf, sizeof(outputbuf),
                 "<html><head><title>Hello Page</title></head>"
                 "<body><h1>Hello, %s!</h1></body></html>", username);

        // Write to the response stream
        fprintf(response, "HTTP/1.1 200 OK\r\n");
        fprintf(response, "Content-Type: text/html\r\n");
        fprintf(response, "Content-Length: %zu\r\n", strlen(outputbuf));
        fprintf(response, "\r\n"); // End of headers
        fprintf(response, "%s", outputbuf);
    }

    // Close the response stream
    fclose(response);
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
    return EXIT_SUCCESS;
}