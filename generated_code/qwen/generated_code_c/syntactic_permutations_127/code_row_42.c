#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void http_hello_page(FILE *request, FILE *response) {
    char buffer[BUFFER_SIZE];
    char username[BUFFER_SIZE];

    // Read the request to find the username
    if (fgets(buffer, sizeof(buffer), request) != NULL) {
        // Assuming the username is sent as "username=[value]" in the request
        const char *prefix = "username=";
        size_t prefix_len = strlen(prefix);
        char *pos = strstr(buffer, prefix);

        if (pos != NULL) {
            pos += prefix_len;
            sscanf(pos, "%s", username);

            // Construct and send the response
            fprintf(response, "HTTP/1.1 200 OK\r\n");
            fprintf(response, "Content-Type: text/plain\r\n");
            fprintf(response, "\r\n");
            fprintf(response, "Hello %s\r\n", username);
        }
    }

    fflush(response);
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