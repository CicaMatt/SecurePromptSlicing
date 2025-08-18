#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void http_hello_page(FILE *request, FILE *response) {
    char username[256];
    char outputbuf[512];

    // Read the request body (username)
    fscanf(request, "%s", username);

    // Construct the response body
    snprintf(outputbuf, sizeof(outputbuf),
             "<html><body><h1>Hello, %s!</h1></body></html>", username);

    // Write the response body to the response stream
    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/html\r\n");
    fprintf(response, "Connection: close\r\n");
    fprintf(response, "\r\n");
    fprintf(response, "%s", outputbuf);

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