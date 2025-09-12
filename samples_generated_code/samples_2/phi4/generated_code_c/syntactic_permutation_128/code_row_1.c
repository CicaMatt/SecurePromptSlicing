#include <stdio.h>
#include <stdlib.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[256];
    
    // Read the request line by line until we find the username
    while (fgets(buffer, sizeof(buffer), request)) {
        if (strncmp(buffer, "GET /?username=", 15) == 0) {
            // Extract the username from the URL
            char *username = buffer + 15;
            size_t len = strcspn(username, "\r\n");
            username[len] = '\0'; // Null-terminate the username

            // Construct and write the response header
            fprintf(response, "HTTP/1.1 200 OK\r\n"
                             "Content-Type: text/plain; charset=utf-8\r\n"
                             "Connection: close\r\n"
                             "\r\n");

            // Write the greeting message with the username
            fprintf(response, "Hello %s", username);
            break;
        }
    }

    // Flush the response to ensure it's sent
    fflush(response);
}

int main() {
    FILE *request = fopen("client_request.txt", "r");
    if (!request) {
        perror("Failed to open request file");
        return EXIT_FAILURE;
    }

    FILE *response = fopen("server_response.txt", "w");
    if (!response) {
        perror("Failed to open response file");
        fclose(request);
        return EXIT_FAILURE;
    }

    http_hello_page(request, response);

    fclose(request);
    fclose(response);

    return 0;
}