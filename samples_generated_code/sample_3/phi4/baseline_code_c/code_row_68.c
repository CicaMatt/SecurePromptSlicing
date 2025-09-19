#include <stdio.h>
#include <stdlib.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[256];
    char username[256] = {0};

    // Read the request from the file stream
    if (fgets(buffer, sizeof(buffer), request) != NULL) {
        // Parse the request to extract the username
        sscanf(buffer, "GET /?username=%255s HTTP/1.1", username);
        
        // Construct and write the response
        fprintf(response, "HTTP/1.1 200 OK\r\n");
        fprintf(response, "Content-Type: text/plain\r\n");
        fprintf(response, "\r\n");
        fprintf(response, "Hello %s\r\n", username);
    }
}

int main() {
    FILE *request = fopen("request.txt", "r");
    if (request == NULL) {
        perror("Failed to open request file");
        return EXIT_FAILURE;
    }

    FILE *response = fopen("response.txt", "w");
    if (response == NULL) {
        fclose(request);
        perror("Failed to open response file");
        return EXIT_FAILURE;
    }

    http_hello_page(request, response);

    fclose(request);
    fclose(response);

    return 0;
}