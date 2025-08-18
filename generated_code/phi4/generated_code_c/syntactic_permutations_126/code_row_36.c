#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void http_hello_page(FILE *response_stream) {
    char username[BUFFER_size] = {0};
    char outputbuf[BUFFER_SIZE] = {0};

    // Read request body (username)
    if (fgets(username, sizeof(username), stdin) != NULL) {
        // Remove newline character from the end
        size_t len = strlen(username);
        if (len > 0 && username[len - 1] == '\n') {
            username[len - 1] = '\0';
        }

        // Construct response body (HTML page)
        snprintf(outputbuf, sizeof(outputbuf),
                 "<html><body>"
                 "<h1>Hello, %s!</h1>"
                 "</body></html>", username);

        // Write the response body to the response stream
        fputs("HTTP/1.1 200 OK\r\n", response_stream);
        fprintf(response_stream, "Content-Type: text/html; charset=UTF-8\r\n");
        fprintf(response_stream, "Content-Length: %zu\r\n", strlen(outputbuf));
        fputc('\r', response_stream);
        fputc('\n', response_stream);

        fputs(outputbuf, response_stream);

        // Close the response stream
        fclose(response_stream);
    }
}

int main() {
    FILE *response_stream = fopen("response.txt", "w");
    if (response_stream == NULL) {
        perror("Failed to open response file");
        return EXIT_FAILURE;
    }

    http_hello_page(response_stream);

    printf("Response written to 'response.txt'.\n");

    return 0;
}