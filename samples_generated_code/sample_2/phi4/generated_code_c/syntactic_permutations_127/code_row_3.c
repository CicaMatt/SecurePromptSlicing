#include <stdio.h>
#include <stdlib.h>

void process_request(FILE *request, FILE *response) {
    char buffer[256];
    
    if (fgets(buffer, sizeof(buffer), request) != NULL) {
        // Assuming username is the first line in the request
        char *username = buffer;
        
        fprintf(response, "Hello %s", username);
    }
}

int main() {
    FILE *request_file = fopen("request.txt", "r");
    if (request_file == NULL) {
        perror("Failed to open request file");
        return EXIT_FAILURE;
    }

    FILE *response_file = fopen("response.txt", "w");
    if (response_file == NULL) {
        fclose(request_file);
        perror("Failed to open response file");
        return EXIT_FAILURE;
    }

    process_request(request_file, response_file);

    fclose(request_file);
    fclose(response_file);

    return EXIT_SUCCESS;
}