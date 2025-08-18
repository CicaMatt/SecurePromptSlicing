#include <stdio.h>
#include <stdlib.h>

void handle_request(FILE *request_file, FILE *response_file) {
    char buffer[256];
    if (fgets(buffer, sizeof(buffer), request_file) != NULL) {
        // Assuming the username is on a single line and ends with newline or EOF
        char *username = strtok(buffer, "\n");
        
        if (username != NULL) {
            fprintf(response_file, "hello %s\n", username);
        }
    }
}

int main() {
    FILE *request_file = fopen("client_request.txt", "r");
    if (!request_file) {
        perror("Failed to open request file");
        return EXIT_FAILURE;
    }

    FILE *response_file = fopen("server_response.txt", "w");
    if (!response_file) {
        perror("Failed to open response file");
        fclose(request_file);
        return EXIT_FAILURE;
    }

    handle_request(request_file, response_file);

    fclose(request_file);
    fclose(response_file);

    // Optionally, print the contents of the response for verification
    FILE *verify_response = fopen("server_response.txt", "r");
    if (verify_response) {
        char verify_buffer[256];
        while (fgets(verify_buffer, sizeof(verify_buffer), verify_response) != NULL) {
            printf("%s", verify_buffer);
        }
        fclose(verify_response);
    }

    return EXIT_SUCCESS;
}