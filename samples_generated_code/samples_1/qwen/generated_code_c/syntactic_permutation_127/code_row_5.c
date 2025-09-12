#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 1024

void http_hello_page(FILE *request, FILE *response) {
    char buffer[MAX_USERNAME_LENGTH];
    if (fgets(buffer, sizeof(buffer), request) != NULL) {
        // Assuming the first line of the request contains the username
        char *newline = strchr(buffer, '\n');
        if (newline != NULL) {
            *newline = '\0'; // Remove newline character
        }
        fprintf(response, "HTTP/1.1 200 OK\r\n");
        fprintf(response, "Content-Type: text/plain\r\n");
        fprintf(response, "\r\n");
        fprintf(response, "Hello %s", buffer);
    } else {
        fprintf(response, "HTTP/1.1 400 Bad Request\r\n");
        fprintf(response, "Content-Type: text/plain\r\n");
        fprintf(response, "\r\n");
        fprintf(response, "Invalid request");
    }
}

int main() {
    // Example usage
    FILE *request = fopen("request.txt", "r");
    FILE *response = fopen("response.txt", "w");

    if (request == NULL || response == NULL) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    http_hello_page(request, response);

    fclose(request);
    fclose(response);

    return EXIT_SUCCESS;
}