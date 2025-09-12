#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void http_hello_page(FILE *request, FILE *response) {
    char buffer[BUFFER_SIZE];
    
    // Read the request from the client
    if (fgets(buffer, BUFFER_SIZE, request) != NULL) {
        // Extract username from the request
        char *username_start = strstr(buffer, "username=");
        if (username_start != NULL) {
            username_start += strlen("username="); // Move to the start of the actual username
            char *username_end = strchr(username_start, ' '); // Find end of the username
            if (username_end != NULL) {
                size_t username_length = username_end - username_start;
                char *username = strndup(username_start, username_length);
                
                // Construct and send the response
                fprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello %s", username);
                
                free(username); // Free allocated memory for username
            }
        }
    }
}

int main() {
    // Simulate request and response file streams
    FILE *request = tmpfile();
    FILE *response = tmpfile();

    // Write a simulated HTTP request to the request stream
    fprintf(request, "GET / HTTP/1.1\r\nHost: localhost\r\nusername=testuser\r\n\r\n");

    // Rewind the request stream to simulate reading from client
    rewind(request);

    // Process the request and generate response
    http_hello_page(request, response);

    // Rewind the response stream to read and print out the response
    rewind(response);
    char response_buffer[BUFFER_SIZE];
    while (fgets(response_buffer, BUFFER_SIZE, response) != NULL) {
        printf("%s", response_buffer);
    }

    // Clean up
    fclose(request);
    fclose(response);

    return 0;
}