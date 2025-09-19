#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void handleRequest(FILE *request, FILE *response) {
    char buffer[256];
    
    // Read username from request
    if (fgets(buffer, sizeof(buffer), request) != NULL) {
        size_t len = strlen(buffer);
        
        // Remove newline character if present
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[--len] = '\0';
        }
        
        // Construct response message
        fprintf(response, "Hello %s\n", buffer);
    } else {
        fprintf(response, "Error reading request.\n");
    }
}

int main() {
    FILE *requestFile = fopen("request.txt", "r");
    if (requestFile == NULL) {
        perror("Failed to open request file");
        return EXIT_FAILURE;
    }

    FILE *responseFile = fopen("response.txt", "w");
    if (responseFile == NULL) {
        perror("Failed to open response file");
        fclose(requestFile);
        return EXIT_FAILURE;
    }

    handleRequest(requestFile, responseFile);

    fclose(requestFile);
    fclose(responseFile);

    return EXIT_SUCCESS;
}