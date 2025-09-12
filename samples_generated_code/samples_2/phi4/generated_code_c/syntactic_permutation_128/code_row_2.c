#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[256];
    
    // Read the request line by line until we find the username
    while (fgets(buffer, sizeof(buffer), request)) {
        if (strncmp(buffer, "GET /?username=", 15) == 0) {
            // Extract the username from the request URL
            char *username_start = buffer + 15;
            char *username_end = strchr(username_start, ' ');
            if (username_end != NULL) {
                *username_end = '\0';  // Null-terminate the username string

                // Construct and send the response
                fprintf(response, "HTTP/1.1 200 OK\r\n");
                fprintf(response, "Content-Type: text/plain\r\n");
                fprintf(response, "\r\n");
                fprintf(response, "hello %s", username_start);
            }
            break;
        }
    }
}

int main() {
    // Simulating request and response as file streams
    FILE *request = fmemopen(
        "GET /?username=JohnDoe HTTP/1.1\r\n"
        "Host: localhost\r\n"
        "\r\n", 
        64, "r");
    
    FILE *response = open_memstream(NULL, NULL);

    http_hello_page(request, response);
    
    // Reset and read the response to print it
    rewind(response);
    char response_buffer[1024];
    fread(response_buffer, sizeof(char), sizeof(response_buffer) - 1, response);
    response_buffer[sizeof(response_buffer) - 1] = '\0';
    printf("%s", response_buffer);

    fclose(request);
    fclose(response);

    return 0;
}


Note: This code uses `fmemopen` and `open_memstream`, which are available in POSIX-compliant systems but may not be portable to all environments. You might need to adjust the test setup if you run this on a non-POSIX system.