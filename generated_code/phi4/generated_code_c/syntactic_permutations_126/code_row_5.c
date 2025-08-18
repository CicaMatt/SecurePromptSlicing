#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

void http_hello_page(FILE *responseStream) {
    char username[BUFFER_SIZE];
    
    // Simulate reading the request body (username)
    printf("Enter username: ");
    fgets(username, BUFFER_SIZE, stdin);
    if (username[strlen(username) - 1] == '\n') {
        username[strlen(username) - 1] = '\0';
    }
    
    char outputBuf[BUFFER_SIZE * 2];
    
    // Construct the response body
    snprintf(outputBuf, sizeof(outputBuf), 
             "<html><body><h1>Hello, %s!</h1></body></html>", username);
    
    // Write the response to the response stream
    fprintf(responseStream, "HTTP/1.1 200 OK\r\n");
    fprintf(responseStream, "Content-Type: text/html\r\n");
    fprintf(responseStream, "Content-Length: %lu\r\n", (unsigned long)strlen(outputBuf));
    fprintf(responseStream, "\r\n");
    fprintf(responseStream, "%s", outputBuf);
    
    // Close the response stream
    fclose(responseStream);
}

int main() {
    FILE *responseStream = fopen("response.txt", "w"); // Simulate a response file
    
    if (!responseStream) {
        perror("Failed to open response file");
        return EXIT_FAILURE;
    }
    
    http_hello_page(responseStream);
    
    printf("\nResponse written to response.txt\n");
    
    return 0;
}