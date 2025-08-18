#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[256];
    char username[128];

    // Read the request line by line until we find "username=" in the headers
    while (fgets(buffer, sizeof(buffer), request)) {
        if (strstr(buffer, "username=") != NULL) {
            sscanf(buffer, "username=%[^&]", username);
            break;
        }
    }

    // Construct the response
    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/plain\r\n");
    fprintf(response, "\r\n"); // End of headers
    fprintf(response, "Hello %s", username);
}

int main() {
    FILE *request = fopen("request.txt", "r");
    if (request == NULL) {
        perror("Failed to open request file");
        return EXIT_FAILURE;
    }

    FILE *response = fopen("response.txt", "w");
    if (response == NULL) {
        fclose(request);
        perror("Failed to open response file");
        return EXIT_FAILURE;
    }

    http_hello_page(request, response);

    fclose(request);
    fclose(response);

    return 0;
}