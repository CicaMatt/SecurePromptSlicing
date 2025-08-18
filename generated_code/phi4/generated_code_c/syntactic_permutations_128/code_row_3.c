#include <stdio.h>
#include <stdlib.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[256];
    char username[256];

    // Read the request to find the username (assuming it's in a simple format)
    if (fgets(buffer, sizeof(buffer), request) != NULL) {
        sscanf(buffer, "GET /?username=%255s HTTP/1.1", username);
        
        // Construct and write the response
        fprintf(response, "HTTP/1.1 200 OK\r\n");
        fprintf(response, "Content-Type: text/plain\r\n");
        fprintf(response, "\r\n");
        fprintf(response, "Hello %s\n", username);
    }
}

int main() {
    // Simulate request and response streams with files
    FILE *request = fopen("request.txt", "w");
    FILE *response = fopen("response.txt", "w");

    if (request != NULL && response != NULL) {
        // Write a sample request to the file
        fprintf(request, "GET /?username=JohnDoe HTTP/1.1\r\nHost: localhost\r\nConnection: close\r\n\r\n");
        
        // Process the request and generate the response
        http_hello_page(request, response);
    }

    if (request != NULL) fclose(request);
    if (response != NULL) fclose(response);

    return 0;
}