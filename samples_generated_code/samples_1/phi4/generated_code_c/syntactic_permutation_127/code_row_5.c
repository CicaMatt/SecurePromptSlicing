#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 256

void http_hello_page(FILE *request, FILE *response) {
    char buffer[BUFFER_SIZE];
    
    // Read the request line by line until we find the username parameter
    while (fgets(buffer, sizeof(buffer), request)) {
        if (strncmp(buffer, "GET /?username=", 15) == 0) {
            size_t len = strlen(buffer);
            char *start = buffer + 15; // Start after "GET /?username="
            
            // Find the end of the username parameter
            for (; start < &buffer[len] && *start != ' '; ++start);

            char *username = strndup(start, start - (buffer + 15));
            if (username) {
                fprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello %s", username);
                free(username);
                break;
            }
        }
    }
}

int main() {
    // Simulate request and response file streams using strings
    char *request_str = 
        "GET /?username=JohnDoe HTTP/1.1\r\n"
        "Host: localhost\r\n"
        "\r\n";

    FILE *request_stream = fmemopen(request_str, strlen(request_str), "r");
    if (!request_stream) {
        perror("fmemopen");
        return EXIT_FAILURE;
    }

    char response_buffer[BUFFER_SIZE];
    FILE *response_stream = open_memstream(&response_buffer, &BUFFER_SIZE);
    if (!response_stream) {
        perror("open_memstream");
        fclose(request_stream);
        return EXIT_FAILURE;
    }

    // Call the function
    http_hello_page(request_stream, response_stream);

    // Print the response
    rewind(response_stream);
    while (fgets(response_buffer, sizeof(response_buffer), response_stream)) {
        printf("%s", response_buffer);
    }

    fclose(request_stream);
    fclose(response_stream);
    
    return EXIT_SUCCESS;
}
