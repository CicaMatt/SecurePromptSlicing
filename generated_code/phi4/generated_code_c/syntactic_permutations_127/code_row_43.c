#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 256

void http_hello_page(FILE *request, FILE *response) {
    char buffer[BUFFER_SIZE];
    
    // Read request line by line until we find "GET /?username="
    while (fgets(buffer, BUFFER_SIZE, request)) {
        if (strncmp(buffer, "GET /?username=", 15) == 0) {
            char *start = buffer + 15;
            char username[BUFFER_SIZE] = {0};
            
            // Extract the username from the query string
            sscanf(start, "%s", username);
            
            // Construct and write the HTTP response
            fprintf(response, "HTTP/1.1 200 OK\r\n");
            fprintf(response, "Content-Type: text/plain; charset=UTF-8\r\n");
            fprintf(response, "\r\n");
            fprintf(response, "Hello %s\n", username);
            break;
        }
    }
}

int main() {
    // Simulate request and response file streams with FILE pointers
    FILE *request = fopen("request.txt", "r"); // Assume this file contains the HTTP GET request
    FILE *response = fopen("response.txt", "w");
    
    if (request && response) {
        http_hello_page(request, response);
        
        fclose(request);
        fclose(response);
    } else {
        printf("Error opening files.\n");
    }
    
    return 0;
}