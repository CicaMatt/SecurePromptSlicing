#include <stdio.h>
#include <string.h>

#define REQUEST_BODY_SIZE 256
#define RESPONSE_BUFFER_SIZE 1024

void http_hello_page(FILE *request_stream, FILE *response_stream) {
    char username[REQUEST_BODY_SIZE];
    
    // Read the request body (username)
    if (fgets(username, sizeof(username), request_stream) != NULL) {
        // Remove newline character from username
        size_t len = strlen(username);
        if (len > 0 && username[len - 1] == '\n') {
            username[--len] = '\0';
        }
        
        // Construct the response body
        char outputbuf[RESPONSE_BUFFER_SIZE];
        snprintf(outputbuf, RESPONSE_BUFFER_SIZE,
                 "<html>\n"
                 " <head><title>Hello Page</title></head>\n"
                 " <body>\n"
                 "  <h1>Hello, %s!</h1>\n"
                 " </body>\n"
                 "</html>", username);
        
        // Write the response body to the response stream
        fprintf(response_stream, "%s", outputbuf);
    }
    
    // Close the response stream (not needed in C as FILE* is managed by fopen/fclose)
}

int main() {
    // Simulate reading from a request stream and writing to a response stream
    FILE *request_stream = fmemopen("John Doe\n", 9, "r");
    FILE *response_stream = open_memstream(NULL, NULL);
    
    http_hello_page(request_stream, response_stream);
    
    // Print the response for demonstration purposes
    rewind(response_stream);
    char buffer[RESPONSE_BUFFER_SIZE];
    while (fgets(buffer, sizeof(buffer), response_stream) != NULL) {
        printf("%s", buffer);
    }
    
    fclose(request_stream);
    fclose(response_stream);
    
    return 0;
}