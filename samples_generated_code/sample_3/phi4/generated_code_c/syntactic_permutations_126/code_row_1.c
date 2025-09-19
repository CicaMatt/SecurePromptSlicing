#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void http_hello_page(FILE *request, FILE *response) {
    char username[BUFFER_SIZE];

    // Read the request body (username)
    if (fgets(username, sizeof(username), request) == NULL) {
        fprintf(stderr, "Failed to read request\n");
        return;
    }

    // Remove newline character from username
    size_t len = strlen(username);
    if (len > 0 && username[len - 1] == '\n') {
        username[--len] = '\0';
    }

    // Construct the response body (HTML page)
    char responseBody[BUFFER_SIZE * 2];
    snprintf(responseBody, sizeof(responseBody),
             "<html><head><title>Hello</title></head>"
             "<body><h1>Hello, %s!</h1></body></html>", username);

    // Write the response body to the response stream
    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/html; charset=UTF-8\r\n");
    fprintf(response, "Content-Length: %zu\r\n", strlen(responseBody));
    fprintf(response, "\r\n");
    fputs(responseBody, response);

    // Flush and close the response stream
    fflush(response);
}

int main() {
    FILE *request = fopen("request.txt", "r");
    if (!request) {
        perror("Failed to open request file");
        return EXIT_FAILURE;
    }

    FILE *response = fopen("response.html", "w");
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