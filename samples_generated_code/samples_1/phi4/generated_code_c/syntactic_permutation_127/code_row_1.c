#include <stdio.h>
#include <stdlib.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[256];
    
    // Read the username from the request
    fgets(buffer, sizeof(buffer), request);
    
    // Remove newline character if present
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
    
    // Extract username assuming "GET /?username=" format
    char *start = strstr(buffer, "username=");
    if (start) {
        start += strlen("username=");
        char *end = strchr(start, ' ');
        if (end) {
            *end = '\0';
        }
        
        // Write the response
        fprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello %s", start);
    } else {
        // Handle case where username is not found
        fprintf(response, "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nUsername not provided");
    }
}

int main() {
    FILE *request = fopen("request.txt", "r");  // Simulated request file stream
    if (!request) {
        perror("Failed to open request file");
        return EXIT_FAILURE;
    }

    FILE *response = fopen("response.txt", "w");  // Simulated response file stream
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