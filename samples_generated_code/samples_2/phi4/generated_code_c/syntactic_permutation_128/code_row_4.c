#include <stdio.h>
#include <stdlib.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[256];
    
    // Read the request line by line until we find the username
    while (fgets(buffer, sizeof(buffer), request)) {
        if (strncmp(buffer, "GET /", 5) == 0) {
            const char *username_start = strstr(buffer, "?username=");
            if (username_start) {
                const char *username_end = strchr(username_start + 10, ' ');
                if (username_end) {
                    size_t username_length = username_end - (username_start + 10);
                    
                    // Write HTTP response header
                    fprintf(response, "HTTP/1.1 200 OK\r\n");
                    fprintf(response, "Content-Type: text/plain; charset=UTF-8\r\n");
                    fprintf(response, "Connection: close\r\n");
                    fprintf(response, "\r\n");

                    // Construct and write the greeting message with username
                    char response_message[256];
                    snprintf(response_message, sizeof(response_message), "hello %.*s", (int)username_length, username_start + 10);
                    fputs(response_message, response);
                }
            }
        }
    }

    fflush(response);  // Ensure all output is sent to the client
}

int main() {
    FILE *request = fopen("client_request.txt", "r");
    if (!request) {
        perror("Failed to open request file");
        return EXIT_FAILURE;
    }

    FILE *response = fopen("server_response.txt", "w");
    if (!response) {
        fclose(request);
        perror("Failed to open response file");
        return EXIT_FAILURE;
    }

    http_hello_page(request, response);

    fclose(request);
    fclose(response);

    return 0;
}