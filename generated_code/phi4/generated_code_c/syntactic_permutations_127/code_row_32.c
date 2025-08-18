#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[256];
    char username[128];

    // Read the request line from the client (assuming a simple GET request)
    if (fgets(buffer, sizeof(buffer), request) != NULL) {
        // Extract the username from the request
        const char *start = strstr(buffer, "username=");
        if (start) {
            start += 9; // Skip past "username="
            const char *end = strchr(start, ' ');
            if (end) {
                size_t len = end - start;
                strncpy(username, start, len);
                username[len] = '\0'; // Null-terminate the string
            }
        }

        // Construct and write the response
        fprintf(response, "HTTP/1.1 200 OK\r\n");
        fprintf(response, "Content-Type: text/plain\r\n");
        fprintf(response, "\r\n");
        if (strlen(username) > 0) {
            fprintf(response, "Hello %s", username);
        } else {
            fprintf(response, "Hello, who?");
        }
    }
}

int main() {
    // Example usage
    FILE *request = fopen("request.txt", "r");
    FILE *response = fopen("response.txt", "w");

    if (request && response) {
        http_hello_page(request, response);

        fclose(request);
        fclose(response);
    }

    return 0;
}