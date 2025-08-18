#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[256];
    
    // Read username from request
    if (fgets(buffer, sizeof(buffer), request) != NULL) {
        // Find the end of the string and replace it with null terminator to remove newline character
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[--len] = '\0';
        }

        // Construct the response message
        fprintf(response, "HTTP/1.1 200 OK\r\n");
        fprintf(response, "Content-Type: text/plain\r\n");
        fprintf(response, "\r\n");
        fprintf(response, "Hello %s", buffer);
    }
}

int main() {
    FILE *request = fopen("request.txt", "r");
    FILE *response = fopen("response.txt", "w");

    if (request && response) {
        http_hello_page(request, response);
    } else {
        perror("Error opening files");
    }

    if (request) fclose(request);
    if (response) fclose(response);

    return 0;
}