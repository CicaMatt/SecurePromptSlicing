#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[256];
    
    // Read the request line from the file stream
    fgets(buffer, sizeof(buffer), request);
    
    // Find the "username=" part in the request string
    const char *username_start = strstr(buffer, "username=");
    if (username_start != NULL) {
        username_start += 9; // Move past "username="
        
        // Find the end of the username
        const char *username_end = strchr(username_start, ' ');
        if (username_end == NULL) {
            username_end = buffer + strlen(buffer);
        }
        
        // Write the response header
        fprintf(response, "HTTP/1.1 200 OK\r\n");
        fprintf(response, "Content-Type: text/plain\r\n");
        fprintf(response, "\r\n");
        
        // Construct and write the hello message
        char response_message[512];
        snprintf(response_message, sizeof(response_message), "Hello %.*s", (int)(username_end - username_start), username_start);
        fputs(response_message, response);
    } else {
        // If no username is found, send a 400 Bad Request response
        fprintf(response, "HTTP/1.1 400 Bad Request\r\n");
        fprintf(response, "Content-Type: text/plain\r\n");
        fprintf(response, "\r\n");
        fputs("Bad Request", response);
    }
}

int main() {
    // Simulate a request and response using temporary files
    FILE *request = fopen("request.txt", "w");
    FILE *response = fopen("response.txt", "w");

    if (request && response) {
        // Write a sample HTTP GET request with a username parameter
        fprintf(request, "GET /?username=JohnDoe HTTP/1.1\r\nHost: example.com\r\nConnection: close\r\n\r\n");
        
        // Process the request and generate a response
        http_hello_page(request, response);
    }

    if (request) fclose(request);
    if (response) fclose(response);

    return 0;
}