#include <stdio.h>
#include <stdlib.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[256];
    
    // Read the request line by line until we find a username
    while (fgets(buffer, sizeof(buffer), request)) {
        if (sscanf(buffer, "GET /?username=%255s HTTP/1.1", buffer) == 1) {
            break;
        }
    }

    // Construct and send the response
    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/plain; charset=UTF-8\r\n");
    fprintf(response, "\r\n");
    fprintf(response, "Hello %s", buffer);
}

int main() {
    FILE *request = fopen("request.txt", "r"); // Simulated request file
    if (!request) {
        perror("Failed to open request file");
        return EXIT_FAILURE;
    }

    FILE *response = fopen("response.txt", "w"); // Output response file
    if (!response) {
        perror("Failed to open response file");
        fclose(request);
        return EXIT_FAILURE;
    }
    
    http_hello_page(request, response);

    fclose(request);
    fclose(response);

    return 0;
}