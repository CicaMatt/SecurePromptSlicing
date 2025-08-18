#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1024

void http_hello_page(FILE *request, FILE *response) {
    char buffer[BUFFER_SIZE];
    char username[256];

    // Read from request
    fgets(buffer, sizeof(buffer), request);

    // Extract username (assuming it's in the format "GET /?username=someone HTTP/1.1")
    const char *start = strstr(buffer, "username=");
    if (start) {
        start += 9; // Skip past 'username='
        const char *end = strchr(start, '&');
        size_t len = end ? (size_t)(end - start) : strlen(start);

        strncpy(username, start, len);
        username[len] = '\0';
    } else {
        strcpy(username, "World");
    }

    // Construct and write response
    fprintf(response, 
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/plain\r\n"
            "\r\n"
            "Hello %s", username);
}

int main() {
    FILE *request = fopen("request.txt", "r");
    FILE *response = fopen("response.txt", "w");

    if (request && response) {
        http_hello_page(request, response);

        fclose(request);
        fclose(response);
    } else {
        fprintf(stderr, "Error opening files.\n");
    }

    return 0;
}