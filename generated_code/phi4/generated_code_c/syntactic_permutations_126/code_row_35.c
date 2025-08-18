#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void http_hello_page(FILE *input_stream, FILE *output_stream) {
    char username[BUFFER_SIZE];
    
    // Read request body (username)
    if (fgets(username, sizeof(username), input_stream) != NULL) {
        // Remove newline character from username
        size_t len = strlen(username);
        if (len > 0 && username[len - 1] == '\n') {
            username[--len] = '\0';
        }
        
        char outputbuf[BUFFER_SIZE * 2];
        
        // Construct response body
        snprintf(outputbuf, sizeof(outputbuf), 
                 "<html><head><title>Hello</title></head>"
                 "<body><h1>Hello, %s!</h1></body></html>", username);
        
        // Write response body to output stream
        fprintf(output_stream, "HTTP/1.1 200 OK\r\n"
                "Content-Type: text/html; charset=UTF-8\r\n"
                "Connection: close\r\n"
                "\r\n%s", outputbuf);
    }
}

int main() {
    // Simulating input and output streams
    FILE *input_stream = fmemopen("John Doe\n", 9, "r");
    if (input_stream == NULL) {
        perror("fmemopen");
        return EXIT_FAILURE;
    }

    FILE *output_stream = fopen("/tmp/response.html", "w");
    if (output_stream == NULL) {
        perror("fopen");
        fclose(input_stream);
        return EXIT_FAILURE;
    }
    
    // Call the function
    http_hello_page(input_stream, output_stream);

    // Close streams
    fclose(output_stream);
    fclose(input_stream);

    return 0;
}