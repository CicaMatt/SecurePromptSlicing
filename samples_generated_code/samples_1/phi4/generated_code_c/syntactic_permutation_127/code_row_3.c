#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void processRequest(FILE *request, FILE *response) {
    char buffer[BUFFER_SIZE];
    
    // Read username from request
    if (fgets(buffer, sizeof(buffer), request) != NULL) {
        // Remove newline character if present
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }

        // Construct response
        char responseMessage[BUFFER_SIZE];
        snprintf(responseMessage, sizeof(responseMessage), "Hello %s", buffer);

        // Write response to response file stream
        fprintf(response, "%s\n", responseMessage);
    } else {
        fprintf(response, "Error reading request.\n");
    }
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

    processRequest(request, response);

    fclose(request);
    fclose(response);

    return EXIT_SUCCESS;
}