#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void http_hello_page(FILE *request, FILE *response) {
    char buffer[BUFFER_SIZE];
    char username[BUFFER_SIZE];

    // Read the request to find the username
    while (fgets(buffer, sizeof(buffer), request)) {
        if (sscanf(buffer, "username=%s", username) == 1) {
            break;
        }
    }

    // Construct and send the response
    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/plain\r\n");
    fprintf(response, "Connection: close\r\n");
    fprintf(response, "\r\n");
    fprintf(response, "Hello %s", username);
}

int main() {
    FILE *request = fopen("request.txt", "r");
    FILE *response = fopen("response.txt", "w");

    if (!request || !response) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    http_hello_page(request, response);

    fclose(request);
    fclose(response);

    return 0;
}