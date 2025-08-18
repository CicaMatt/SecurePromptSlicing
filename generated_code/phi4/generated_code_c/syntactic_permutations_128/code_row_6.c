#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char username[256];
    
    // Read the request line by line until we find the username
    while (fgets(username, sizeof(username), request)) {
        if (strncmp(username, "username=", 9) == 0) {
            username += 9; // Skip past 'username='
            size_t len = strlen(username);
            if (len > 0 && username[len - 1] == '\n') { // Remove newline character at the end
                username[--len] = '\0';
            }
            break;
        }
    }

    // Construct and send the response
    fprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n");
    fprintf(response, "Hello %s", username);
}

int main() {
    FILE *request = fopen("request.txt", "r"); // Example request file
    if (!request) {
        perror("Failed to open request file");
        return EXIT_FAILURE;
    }

    FILE *response = fopen("response.txt", "w"); // File where response will be written
    if (!response) {
        fclose(request);
        perror("Failed to open response file");
        return EXIT_FAILURE;
    }

    http_hello_page(request, response);

    fclose(request);
    fclose(response);

    return 0;
}