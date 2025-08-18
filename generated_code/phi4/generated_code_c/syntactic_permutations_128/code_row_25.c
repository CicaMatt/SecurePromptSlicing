#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[256];
    
    // Read request line by line until we find the username part
    while (fgets(buffer, sizeof(buffer), request)) {
        if (strncmp(buffer, "GET /", 5) == 0) {
            // Extracting username from query string (e.g., GET /?username=John)
            char *query = strstr(buffer, "?");
            if (query) {
                char *username = strchr(query + 1, '=');
                if (username && *(++username)) { // Ensure there's a username after '='
                    fprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n");
                    fprintf(response, "hello %s", username);
                } else {
                    fprintf(response, "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\n");
                    fprintf(response, "No username provided.");
                }
            } else {
                fprintf(response, "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\n");
                fprintf(response, "Malformed request.");
            }
        }
    }
}

int main() {
    FILE *request = fopen("client_request.txt", "r");
    if (!request) {
        perror("Failed to open client request file");
        return EXIT_FAILURE;
    }

    FILE *response = fopen("server_response.txt", "w");
    if (!response) {
        perror("Failed to open server response file");
        fclose(request);
        return EXIT_FAILURE;
    }

    http_hello_page(request, response);

    fclose(request);
    fclose(response);

    return 0;
}