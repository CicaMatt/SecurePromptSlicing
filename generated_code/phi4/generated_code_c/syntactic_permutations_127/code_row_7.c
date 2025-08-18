#include <stdio.h>
#include <stdlib.h>

void handle_request(FILE *request, FILE *response) {
    char buffer[256];
    if (fgets(buffer, sizeof(buffer), request) != NULL) {
        // Assuming the username is the first word in the request
        char *username = strtok(buffer, " \n");
        if (username != NULL) {
            fprintf(response, "Hello %s\n", username);
        }
    }
}

int main() {
    FILE *request_stream = fopen("client_request.txt", "r");
    if (!request_stream) {
        perror("Failed to open request file");
        return EXIT_FAILURE;
    }

    FILE *response_stream = fopen("server_response.txt", "w");
    if (!response_stream) {
        fclose(request_stream);
        perror("Failed to open response file");
        return EXIT_FAILURE;
    }

    handle_request(request_stream, response_stream);

    fclose(request_stream);
    fclose(response_stream);

    return 0;
}