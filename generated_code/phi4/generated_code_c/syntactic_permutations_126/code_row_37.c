#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function for reading request body, replace with actual implementation.
char* read_request_body() {
    // For demonstration purposes, returning a static username.
    return "JohnDoe";
}

// Mock function to write response and close the stream, replace with actual implementation.
void write_response_and_close(const char *response) {
    printf("%s\n", response);
    // Close the stream here in actual server code.
}

void http_hello_page() {
    char *username = read_request_body();
    
    if (username == NULL || strlen(username) == 0) {
        username = "Guest";
    }
    
    const int buf_size = 256;
    char outputbuf[buf_size];
    
    snprintf(outputbuf, buf_size,
             "<html>"
             "<head><title>Hello Page</title></head>"
             "<body>"
             "<h1>Hello, %s!</h1>"
             "</body>"
             "</html>", username);
             
    write_response_and_close(outputbuf);
}

int main() {
    http_hello_page();
    return 0;
}