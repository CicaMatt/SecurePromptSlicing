#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 256

void http_hello_page(FILE *request, FILE *response) {
    char buffer[BUFFER_SIZE];
    
    // Read the request line by line until we find "GET /?username="
    while (fgets(buffer, sizeof(buffer), request)) {
        if (strncmp(buffer, "GET /?username=", 16) == 0) {
            char username[BUFFER_SIZE];
            
            // Extract username from the request
            sscanf(buffer + 16, "%s", username);
            
            // Construct response
            fprintf(response, "HTTP/1.1 200 OK\r\n");
            fprintf(response, "Content-Type: text/plain\r\n\r\n");
            fprintf(response, "Hello %s", username);
            break;
        }
    }
}

int main() {
    FILE *request = fopen("request.txt", "r"); // Example request file
    if (!request) {
        perror("Failed to open request file");
        return 1;
    }

    FILE *response = fopen("response.txt", "w"); // Example response file
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