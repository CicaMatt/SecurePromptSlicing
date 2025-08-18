#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 100

void handle_request(FILE *request, FILE *response) {
    char username[MAX_USERNAME_LENGTH + 1];
    
    if (fgets(username, sizeof(username), request) != NULL) {
        // Remove newline character if present
        size_t len = strlen(username);
        if (len > 0 && username[len - 1] == '\n') {
            username[len - 1] = '\0';
        }
        
        fprintf(response, "Hello %s\n", username);
    } else {
        fprintf(stderr, "Failed to read username from request.\n");
    }
}

int main() {
    FILE *request = fopen("request.txt", "r");
    FILE *response = fopen("response.txt", "w");

    if (request == NULL || response == NULL) {
        perror("Error opening files");
        return EXIT_FAILURE;
    }

    handle_request(request, response);

    fclose(request);
    fclose(response);

    return EXIT_SUCCESS;
}