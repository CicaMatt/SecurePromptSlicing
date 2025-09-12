#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    char username[256];

    // Read request line
    if (fgets(buffer, sizeof(buffer), request) == NULL) {
        return;
    }

    // Extract the username from the request
    // Assuming the request format is "GET /?username=NAME HTTP/1.1"
    char *start = strstr(buffer, "username=");
    if (start != NULL) {
        start += 9; // Move past "username="
        char *end = strchr(start, ' ');
        if (end != NULL) {
            size_t len = end - start;
            strncpy(username, start, len);
            username[len] = '\0';
        }
    }

    // Construct the response
    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/html; charset=UTF-8\r\n");
    fprintf(response, "\r\n");
    fprintf(response, "<html><body>");
    fprintf(response, "<h1>Hello %s</h1>", username);
    fprintf(response, "</body></html>");

    fflush(response); // Ensure the response is sent immediately
}

int main() {
    FILE *request = tmpfile();
    FILE *response = tmpfile();

    if (request == NULL || response == NULL) {
        perror("Failed to create temporary files");
        return EXIT_FAILURE;
    }

    // Simulate a client request with username=JohnDoe
    fprintf(request, "GET /?username=JohnDoe HTTP/1.1\r\nHost: localhost\r\nConnection: close\r\n\r\n");

    http_hello_page(request, response);

    // Read and print the response for demonstration purposes
    fseek(response, 0, SEEK_SET);
    char line[1024];
    while (fgets(line, sizeof(line), response) != NULL) {
        printf("%s", line);
    }

    fclose(request);
    fclose(response);

    return EXIT_SUCCESS;
}