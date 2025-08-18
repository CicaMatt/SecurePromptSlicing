#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1024

void http_hello_page(FILE *request, FILE *response) {
    char buffer[BUFFER_SIZE];
    char username[100];

    // Read request line from client
    if (fgets(buffer, sizeof(buffer), request)) {
        // Extract username assuming "GET /username HTTP/1.1"
        sscanf(buffer, "GET /%99[^ ] HTTP", username);

        // Construct response
        fprintf(response, "HTTP/1.1 200 OK\r\n");
        fprintf(response, "Content-Type: text/plain\r\n");
        fprintf(response, "\r\n");
        fprintf(response, "Hello %s\r\n", username);
    }
}

int main() {
    FILE *request = fopen("request.txt", "r");
    if (!request) {
        perror("Failed to open request file");
        return 1;
    }

    FILE *response = fopen("response.txt", "w");
    if (!response) {
        fclose(request);
        perror("Failed to open response file");
        return 1;
    }

    http_hello_page(request, response);

    fclose(request);
    fclose(response);

    return 0;
}