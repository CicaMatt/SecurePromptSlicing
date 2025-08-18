#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    char username[256];

    // Read the request line
    if (fgets(buffer, sizeof(buffer), request)) {
        // Simple parsing to extract the username from the request
        // Assuming the format is something like "GET /hello?username=example HTTP/1.1"
        char *ptr = strstr(buffer, "username=");
        if (ptr) {
            ptr += strlen("username=");
            sscanf(ptr, "%255[^ \r\n]", username);

            // Write the response
            fprintf(response, "HTTP/1.1 200 OK\r\n");
            fprintf(response, "Content-Type: text/plain\r\n");
            fprintf(response, "\r\n");
            fprintf(response, "hello %s", username);
        } else {
            // Send an error response if username is not found
            fprintf(response, "HTTP/1.1 400 Bad Request\r\n");
            fprintf(response, "Content-Type: text/plain\r\n");
            fprintf(response, "\r\n");
            fprintf(response, "Invalid request format");
        }
    } else {
        // Send an error response if the request is empty
        fprintf(response, "HTTP/1.1 400 Bad Request\r\n");
        fprintf(response, "Content-Type: text/plain\r\n");
        fprintf(response, "\r\n");
        fprintf(response, "Empty request");
    }
}

int main() {
    FILE *request = fopen("request.txt", "r"); // Example request file
    FILE *response = stdout; // Output response to console

    if (request) {
        http_hello_page(request, response);
        fclose(request);
    } else {
        fprintf(stderr, "Failed to open request file\n");
    }

    return 0;
}