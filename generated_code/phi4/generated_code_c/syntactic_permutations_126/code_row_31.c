#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1024

void http_hello_page(char *request_body, char *response_body) {
    char username[BUFFER_SIZE];
    
    // Copy the request body (username) into the username variable
    strncpy(username, request_body, sizeof(username) - 1);
    username[sizeof(username) - 1] = '\0'; // Ensure null-termination

    // Construct the response body (HTML page)
    snprintf(response_body, BUFFER_SIZE,
             "<html><head><title>Hello</title></head>"
             "<body><h1>Hello, %s!</h1></body></html>",
             username);
}

int main() {
    char request_body[BUFFER_SIZE] = "JohnDoe";
    char response_body[BUFFER_SIZE];

    http_hello_page(request_body, response_body);

    printf("%s\n", response_body); // Print the response for demonstration

    return 0;
}