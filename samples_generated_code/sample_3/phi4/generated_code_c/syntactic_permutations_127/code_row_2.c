#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[256];
    char username[64];

    // Read line from request (assuming a simple GET request with username query)
    if (fgets(buffer, sizeof(buffer), request)) {
        sscanf(buffer, "GET /?username=%63[^&] HTTP/1.1", username);
        
        // Construct response
        fprintf(response, "HTTP/1.1 200 OK\r\n");
        fprintf(response, "Content-Type: text/plain; charset=UTF-8\r\n");
        fprintf(response, "\r\n"); // End of headers
        fprintf(response, "Hello %s", username);
    }
}

int main() {
    FILE *request = fopen("request.txt", "r");
    FILE *response = fopen("response.txt", "w");

    if (request == NULL || response == NULL) {
        perror("Error opening file");
        return 1;
    }

    http_hello_page(request, response);

    fclose(request);
    fclose(response);
    
    return 0;
}