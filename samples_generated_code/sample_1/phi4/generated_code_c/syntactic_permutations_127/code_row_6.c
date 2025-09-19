#include <stdio.h>
#include <stdlib.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[256];
    int bytesRead;

    // Read username from request
    bytesRead = fread(buffer, 1, sizeof(buffer), request);
    
    if (bytesRead > 0 && buffer[bytesRead - 1] == '\n') {
        buffer[bytesRead - 1] = '\0'; // Remove newline character
    } else {
        fputs("Error: Invalid input.", response);
        return;
    }

    // Construct and write the response
    fprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello %s", buffer);
}

int main() {
    FILE *request = fopen("request.txt", "r");
    if (request == NULL) {
        perror("Error opening request file");
        return EXIT_FAILURE;
    }

    FILE *response = fopen("response.txt", "w");
    if (response == NULL) {
        perror("Error opening response file");
        fclose(request);
        return EXIT_FAILURE;
    }

    http_hello_page(request, response);

    fclose(request);
    fclose(response);
    return 0;
}