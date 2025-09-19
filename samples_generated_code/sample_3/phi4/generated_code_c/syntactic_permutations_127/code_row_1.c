#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[256];
    
    // Read from request file stream (assuming username is on a single line)
    if (fgets(buffer, sizeof(buffer), request) != NULL) {
        // Extract username assuming format "username: [actual username]"
        char *username = strtok(buffer, ":");
        if (username != NULL) {
            username++; // Move to the start of the actual username
            // Construct response message
            fprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello %s", username);
        }
    } else {
        // Handle error if reading from request fails
        fprintf(response, "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nFailed to read request.");
    }
}

int main() {
    // Example usage of http_hello_page function
    FILE *request = fopen("request.txt", "r");
    if (request == NULL) {
        perror("Failed to open request file");
        return EXIT_FAILURE;
    }

    FILE *response = fopen("response.txt", "w");
    if (response == NULL) {
        perror("Failed to open response file");
        fclose(request);
        return EXIT_FAILURE;
    }

    http_hello_page(request, response);

    fclose(request);
    fclose(response);

    return 0;
}