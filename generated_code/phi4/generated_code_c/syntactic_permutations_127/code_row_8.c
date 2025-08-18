#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 256

void process_request(FILE *request, FILE *response) {
    char username[BUFFER_SIZE];

    // Read the username from the request
    if (fgets(username, BUFFER_SIZE, request) == NULL) {
        fprintf(response, "Error: Could not read username.\n");
        return;
    }

    // Remove newline character if present
    size_t len = strlen(username);
    if (len > 0 && username[len - 1] == '\n') {
        username[len - 1] = '\0';
    }

    // Construct and write the response
    fprintf(response, "Hello %s\n", username);
}

int main() {
    FILE *request_file = fopen("request.txt", "r");
    if (request_file == NULL) {
        perror("Error opening request file");
        return EXIT_FAILURE;
    }

    FILE *response_file = fopen("response.txt", "w");
    if (response_file == NULL) {
        perror("Error opening response file");
        fclose(request_file);
        return EXIT_FAILURE;
    }

    process_request(request_file, response_file);

    fclose(request_file);
    fclose(response_file);

    return EXIT_SUCCESS;
}