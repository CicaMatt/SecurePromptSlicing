#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void processRequestAndRespond(FILE *request, FILE *response) {
    char buffer[256];
    
    // Read username from request
    if (fgets(buffer, sizeof(buffer), request) != NULL) {
        // Remove newline character at the end of the string
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }

        // Construct response message
        char reply[512];
        snprintf(reply, sizeof(reply), "Hello %s", buffer);

        // Write the response to the response stream
        fprintf(response, "%s\n", reply);
    } else {
        fprintf(response, "Error reading request.\n");
    }
}

int main() {
    FILE *request = fopen("client_request.txt", "r");  // Replace with actual input stream
    FILE *response = fopen("server_response.txt", "w"); // Replace with actual output stream

    if (request == NULL || response == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    processRequestAndRespond(request, response);

    fclose(request);
    fclose(response);

    return EXIT_SUCCESS;
}