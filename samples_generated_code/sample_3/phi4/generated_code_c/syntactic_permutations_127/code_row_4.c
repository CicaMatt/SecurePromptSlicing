#include <stdio.h>
#include <stdlib.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[256];
    char username[256];

    // Read request line by line until we find one that contains a "username="
    while (fgets(buffer, sizeof(buffer), request)) {
        if (sscanf(buffer, "%*s %*s %*s %*[^=]=%255s", username) == 1) {
            break;
        }
    }

    // Construct the response
    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/plain; charset=UTF-8\r\n");
    fprintf(response, "\r\n"); // End of headers
    fprintf(response, "Hello %s", username);
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

    return EXIT_SUCCESS;
}