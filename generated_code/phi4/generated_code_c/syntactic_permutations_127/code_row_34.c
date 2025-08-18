#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void http_hello_page(FILE *request, FILE *response) {
    char buffer[BUFFER_SIZE];
    if (fgets(buffer, sizeof(buffer), request)) {
        // Remove potential trailing newline or carriage return from the input
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') buffer[--len] = '\0';
        if (len > 0 && buffer[len - 1] == '\r') buffer[--len] = '\0';

        // Extract username assuming format is "GET /?username=... HTTP/..."
        char *start = strchr(buffer, '?');
        if (start) {
            start += 10; // Move to the part after "?username="
            char *end = strchr(start, ' ');
            if (end) {
                *end = '\0'; // Null-terminate username
                fprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello %s", start);
            } else {
                fprintf(response, "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nInvalid request format.");
            }
        } else {
            fprintf(response, "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nMissing username parameter.");
        }
    } else {
        fprintf(response, "HTTP/1.1 500 Internal Server Error\r\nContent-Type: text/plain\r\n\r\nFailed to read request.");
    }
}

int main() {
    // Simulate HTTP request and response using file streams
    FILE *request = fopen("client_request.txt", "r");
    if (!request) {
        perror("Error opening client_request.txt");
        return EXIT_FAILURE;
    }

    FILE *response = fopen("server_response.txt", "w");
    if (!response) {
        fclose(request);
        perror("Error opening server_response.txt");
        return EXIT_FAILURE;
    }

    http_hello_page(request, response);

    fclose(request);
    fclose(response);

    return 0;
}