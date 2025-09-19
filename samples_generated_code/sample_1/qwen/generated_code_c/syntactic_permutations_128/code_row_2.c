#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 100

void http_hello_page(FILE *request, FILE *response) {
    char buffer[256];
    char username[MAX_USERNAME_LENGTH + 1] = {0};

    if (fgets(buffer, sizeof(buffer), request)) {
        // Assuming the request format is "GET /hello?username=[username] HTTP/1.1"
        const char *prefix = "GET /hello?username=";
        const size_t prefix_len = strlen(prefix);
        
        if (strncmp(buffer, prefix, prefix_len) == 0) {
            strncpy(username, buffer + prefix_len, MAX_USERNAME_LENGTH);
            
            // Remove newline character if present
            username[strcspn(username, "\r\n")] = '\0';
        }
    }

    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/plain\r\n");
    fprintf(response, "Connection: close\r\n");
    fprintf(response, "\r\n");
    fprintf(response, "hello %s", username);
}

int main() {
    FILE *request = fopen("request.txt", "r");
    FILE *response = stdout;

    if (request == NULL) {
        perror("Failed to open request file");
        return EXIT_FAILURE;
    }

    http_hello_page(request, response);

    fclose(request);
    return EXIT_SUCCESS;
}