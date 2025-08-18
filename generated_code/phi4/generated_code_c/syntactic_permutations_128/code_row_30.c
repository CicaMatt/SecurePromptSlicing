#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1024

void http_hello_page(FILE *request, FILE *response) {
    char username[BUFFER SIZE] = {0};
    
    // Read the request line (assuming it's in a simple format)
    if (fgets(request->buffer, sizeof(request->buffer), request)) {
        // Extract the username from the request
        sscanf(request->buffer, "GET /?username=%[^&]\n", username);

        // Construct the response message
        fprintf(response, "HTTP/1.1 200 OK\r\n");
        fprintf(response, "Content-Type: text/plain\r\n");
        fprintf(response, "\r\n"); // End of headers
        fprintf(response, "Hello %s!\r\n", username);
    }
}

int main() {
    FILE *request = fopen("client_request.txt", "r");
    if (!request) {
        perror("Failed to open request file");
        return 1;
    }

    FILE *response = fopen("server_response.txt", "w");
    if (!response) {
        perror("Failed to open response file");
        fclose(request);
        return 1;
    }

    http_hello_page(request, response);

    fclose(request);
    fclose(response);

    return 0;
}