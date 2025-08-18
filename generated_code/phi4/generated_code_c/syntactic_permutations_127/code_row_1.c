#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[256];
    
    // Read the entire request (assuming it's small enough for this buffer)
    fgets(buffer, sizeof(buffer), request);
    
    // Extract username from a simple GET request format
    sscanf(buffer, "GET /?username=%255s", buffer); // Assuming username is URL-encoded
    
    // Construct and write response
    fprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello %s", buffer);
}

int main() {
    FILE *request = fopen("request.txt", "r"); // Simulate request file stream
    FILE *response = fopen("response.txt", "w"); // Simulate response file stream
    
    if (request == NULL || response == NULL) {
        perror("Error opening files");
        return 1;
    }
    
    http_hello_page(request, response);
    
    fclose(request);
    fclose(response);

    return 0;
}