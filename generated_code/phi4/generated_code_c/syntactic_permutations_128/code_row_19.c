#include <stdio.h>
#include <stdlib.h>

typedef struct {
    FILE *file;
} Request;

typedef struct {
    FILE *file;
} Response;

void http_hello_page(Request request, Response response) {
    char username[256];
    
    // Read the username from the request file stream
    if (fgets(username, sizeof(username), request.file)) {
        // Remove newline character if present
        size_t len = strlen(username);
        if (len > 0 && username[len - 1] == '\n') {
            username[len - 1] = '\0';
        }

        // Construct the response message
        char response_message[512];
        snprintf(response_message, sizeof(response_message), "hello %s", username);

        // Write the response to the response file stream
        fprintf(response.file, "%s\n", response_message);
    }
}

int main() {
    FILE *request_file = fopen("request.txt", "r");
    if (!request_file) {
        perror("Failed to open request file");
        return EXIT_FAILURE;
    }

    FILE *response_file = fopen("response.txt", "w");
    if (!response_file) {
        perror("Failed to open response file");
        fclose(request_file);
        return EXIT_FAILURE;
    }

    Request request = {request_file};
    Response response = {response_file};

    http_hello_page(request, response);

    fclose(request_file);
    fclose(response_file);

    return EXIT_SUCCESS;
}