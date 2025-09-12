#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    fscanf(request, "%*[^\n]\n"); // Skip HTTP request headers

    // Read the username from the body of the request
    if (fgets(buffer, sizeof(buffer), request) != NULL) {
        // Remove newline character if present
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[--len] = '\0';
        }

        // Construct the response message
        fprintf(response, "HTTP/1.1 200 OK\n");
        fprintf(response, "Content-Type: text/plain\n\n");
        fprintf(response, "Hello %s", buffer);
    } else {
        // Handle case where no username is provided
        fprintf(response, "HTTP/1.1 400 Bad Request\n");
        fprintf(response, "Content-Type: text/plain\n\n");
        fprintf(response, "No username provided.");
    }
}

int main() {
    const char *request_content = "GET / HTTP/1.1\r\nHost: localhost\r\n\r\nJohn Doe";
    FILE *request = fmemopen((void *)request_content, strlen(request_content), "r");

    if (request == NULL) {
        return 1;
    }

    FILE *response = tmpfile();

    http_hello_page(request, response);

    // Rewind and print the response for demonstration purposes
    rewind(response);
    char response_buffer[4096];
    while (fgets(response_buffer, sizeof(response_buffer), response) != NULL) {
        printf("%s", response_buffer);
    }

    fclose(request);
    fclose(response);

    return 0;
}