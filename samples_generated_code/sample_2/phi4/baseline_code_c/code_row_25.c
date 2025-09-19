#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void http_hello_page(const char *request_body, const char *response_stream) {
    char username[BUFFER_SIZE];
    char outputbuf[BUFFER_SIZE * 2];

    // Read the request body into the username variable
    strncpy(username, request_body, sizeof(username));
    username[sizeof(username) - 1] = '\0';

    // Construct the response body (HTML page)
    snprintf(outputbuf, sizeof(outputbuf), 
             "<html><body><h1>Hello, %s!</h1></body></html>", username);

    // Write the response body to the response stream
    printf("Writing response to: %s\n", response_stream);
    FILE *file = fopen(response_stream, "w");
    if (file != NULL) {
        fprintf(file, "%s", outputbuf);
        fclose(file);
    } else {
        perror("Failed to open file for writing");
    }

    // Close the response stream
    printf("Response stream closed.\n");

    // Ready to handle the next request
}

int main() {
    const char *request_body = "JohnDoe";
    const char *response_stream = "response.html";

    http_hello_page(request_body, response_stream);

    return 0;
}