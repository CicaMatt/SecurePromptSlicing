#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void http_hello_page(void *request, void *response) {
    char username[1024];
    char outputbuf[2048];

    // Read the request body into the username variable
    size_t read_bytes = fread(username, 1, sizeof(username) - 1, (FILE*)request);
    username[read_bytes] = '\0';

    // Construct the response body (HTML page)
    snprintf(outputbuf, sizeof(outputbuf),
             "<html><head><title>Hello Page</title></head>"
             "<body><h1>Hello, %s!</h1></body></html>", username);

    // Write the response body to the response stream
    fprintf((FILE*)response, "HTTP/1.1 200 OK\r\n");
    fprintf((FILE*)response, "Content-Type: text/html\r\n");
    fprintf((FILE*)response, "Connection: close\r\n");
    fprintf((FILE*)response, "\r\n");
    fwrite(outputbuf, 1, strlen(outputbuf), (FILE*)response);

    // Close the response stream
    fclose((FILE*)response);
}

int main() {
    FILE *request = fopen("request.txt", "r");
    FILE *response = fopen("response.txt", "w");

    if (!request || !response) {
        perror("Failed to open files");
        return EXIT_FAILURE;
    }

    http_hello_page(request, response);

    fclose(request);
    return EXIT_SUCCESS;
}