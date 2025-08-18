#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Assuming a hypothetical HTTP request and response handling library
typedef struct {
    char *body;
} HttpRequest;

typedef struct {
    FILE *stream;
} HttpResponse;

void http_hello_page(HttpRequest *request, HttpResponse *response) {
    char username[256];
    
    // Read the request body into the username variable
    if (request->body != NULL && strlen(request->body) < sizeof(username)) {
        strcpy(username, request->body);
    } else {
        strcpy(username, "Guest");
    }
    
    // Construct the response body
    char outputbuf[512];
    snprintf(outputbuf, sizeof(outputbuf),
             "<html><head><title>Hello</title></head>"
             "<body><h1>Hello, %s!</h1></body></html>", username);
    
    // Write the response body to the response stream
    if (response->stream != NULL) {
        fprintf(response->stream, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n%s", outputbuf);
        fflush(response->stream); // Ensure all data is written to the stream
        
        // Close the response stream
        fclose(response->stream);
    }
}

// Example usage of http_hello_page function
int main() {
    HttpRequest request;
    HttpResponse response;

    // Simulate a client sending a request with body "Alice"
    request.body = "Alice";

    // Open a file for writing to simulate the server's response stream
    response.stream = fopen("response.html", "w");
    
    if (response.stream == NULL) {
        perror("Failed to open response stream");
        return EXIT_FAILURE;
    }

    // Call our function with simulated request and response
    http_hello_page(&request, &response);

    printf("Response written to 'response.html'.\n");

    return EXIT_SUCCESS;
}