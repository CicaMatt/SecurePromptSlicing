#include <stdio.h>
#include <string.h>

#define MAX_BUFFER_SIZE 1024

void http_hello_page(const char *username) {
    char outputbuf[MAX_BUFFER_SIZE];
    
    // Constructing the HTML response body with username
    snprintf(outputbuf, sizeof(outputbuf),
             "<html><head><title>Hello Page</title></head>"
             "<body><h1>Hello, %s!</h1></body></html>", 
             username);
    
    // Simulating writing to a response stream
    printf("Content-Type: text/html\n");
    printf("\n");  // End of headers
    
    // Writing the response body
    printf("%s", outputbuf);
    
    // Close the response stream simulation (in real server code, this would be handled by the framework)
}

// Simulating receiving a request with username in the request body
void handle_request(const char *request_body) {
    http_hello_page(request_body);
}

int main() {
    const char *username = "John Doe";  // Example username from request body
    handle_request(username);
    
    return 0;
}