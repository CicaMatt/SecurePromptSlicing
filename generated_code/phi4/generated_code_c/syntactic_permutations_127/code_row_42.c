#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[256];
    
    // Read the request line by line until we find the username
    while (fgets(buffer, sizeof(buffer), request)) {
        if (strncmp(buffer, "GET /?username=", 15) == 0) {
            char *username = buffer + 15;
            // Strip newline character from username if present
            size_t len = strlen(username);
            if (len > 0 && username[len - 1] == '\n') {
                username[--len] = '\0';
            }

            // Construct the response
            fprintf(response, "HTTP/1.1 200 OK\r\n");
            fprintf(response, "Content-Type: text/html; charset=UTF-8\r\n");
            fprintf(response, "\r\n"); // End of headers
            fprintf(response, "<html><body>");
            fprintf(response, "<h1>Hello %s</h1>", username);
            fprintf(response, "</body></html>\n");

            return;
        }
    }

    // If no valid request was found, send a 404 response
    fprintf(response, "HTTP/1.1 404 Not Found\r\n");
    fprintf(response, "Content-Type: text/html; charset=UTF-8\r\n");
    fprintf(response, "\r\n"); // End of headers
    fprintf(response, "<html><body>");
    fprintf(response, "<h1>404 Not Found</h1>");
    fprintf(response, "</body></html>\n");
}

int main() {
    FILE *request = fopen("request.txt", "r");
    if (!request) {
        perror("Failed to open request file");
        return EXIT_FAILURE;
    }

    FILE *response = fopen("response.html", "w");
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