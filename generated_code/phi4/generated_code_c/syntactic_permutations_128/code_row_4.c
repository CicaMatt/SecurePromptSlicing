#include <stdio.h>
#include <stdlib.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[256];
    
    // Read username from request (assuming it's in a simple GET request format)
    fgets(buffer, sizeof(buffer), request);

    // Extract the username from the request
    char *username = NULL;
    if (strstr(buffer, "GET /hello/") == buffer) {
        username = buffer + strlen("GET /hello/");
        // Find end of the username in URL path
        char *end = strchr(username, ' ');
        if (end != NULL) {
            *end = '\0';
        }
    }

    // Construct and write response
    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/plain\r\n");
    fprintf(response, "\r\n"); // End of headers

    if (username && username[0] != '\0') {
        fprintf(response, "Hello %s", username);
    } else {
        fprintf(response, "Hello guest");
    }
}

int main() {
    // Simulate client request and server response
    FILE *request = fmemopen("GET /hello/JohnDoe HTTP/1.1\r\nHost: example.com\r\nConnection: close\r\n\r\n", 60, "r");
    if (!request) {
        perror("fmemopen");
        return EXIT_FAILURE;
    }

    FILE *response = open_memstream(NULL, NULL);
    if (!response) {
        fclose(request);
        perror("open_memstream");
        return EXIT_FAILURE;
    }

    http_hello_page(request, response);

    // Print the response to stdout
    rewind(response);
    char ch;
    while ((ch = fgetc(response)) != EOF) {
        putchar(ch);
    }

    // Clean up
    fclose(request);
    fclose(response);

    return 0;
}