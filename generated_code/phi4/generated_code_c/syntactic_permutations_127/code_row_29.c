#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void http_hello_page(FILE *request, FILE *response) {
    char buffer[BUFFER_SIZE];
    
    // Read the request line by line until we find a line starting with "username="
    while (fgets(buffer, sizeof(buffer), request)) {
        if (strncmp(buffer, "GET /?username=", 15) == 0) {
            char *username_start = strchr(buffer + 15, '=') + 1;
            char username[BUFFER_SIZE];
            
            // Extract the username from the buffer
            size_t len = strlen(username_start);
            if (len < sizeof(username)) {
                strncpy(username, username_start, len);
                username[len] = '\0';
            } else {
                username[0] = '\0'; // Empty username if too long
            }
            
            // Construct and write the response
            fprintf(response, "HTTP/1.1 200 OK\r\n");
            fprintf(response, "Content-Type: text/plain\r\n");
            fprintf(response, "\r\n");
            fprintf(response, "Hello %s", username);
            break;
        }
    }
}

int main() {
    // Example usage
    const char *request_data = 
        "GET /?username=john_doe HTTP/1.1\r\n"
        "Host: localhost\r\n"
        "\r\n";

    FILE *request_stream = fmemopen((void *)request_data, strlen(request_data), "r");
    if (!request_stream) {
        perror("fmemopen failed");
        return EXIT_FAILURE;
    }

    FILE *response_stream = tmpfile();
    if (!response_stream) {
        perror("tmpfile failed");
        fclose(request_stream);
        return EXIT_FAILURE;
    }

    http_hello_page(request_stream, response_stream);

    // Move the file pointer to the beginning of the response stream
    rewind(response_stream);

    // Read and print the response content
    char buffer[BUFFER_SIZE];
    while (fgets(buffer, sizeof(buffer), response_stream)) {
        printf("%s", buffer);
    }

    fclose(request_stream);
    fclose(response_stream);

    return EXIT_SUCCESS;
}