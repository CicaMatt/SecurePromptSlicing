#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 100

void http_hello_page(FILE *request, FILE *response) {
    char username[MAX_USERNAME_LENGTH + 1];
    
    if (fgets(username, sizeof(username), request) != NULL) {
        // Remove newline character if present
        size_t len = strlen(username);
        if (len > 0 && username[len - 1] == '\n') {
            username[len - 1] = '\0';
        }
        
        fprintf(response, "hello %s", username);
    } else {
        fprintf(response, "hello unknown");
    }
}

int main() {
    FILE *request = fopen("request.txt", "r");
    FILE *response = stdout; // Assuming response is written to standard output

    if (request == NULL) {
        perror("Failed to open request file");
        return EXIT_FAILURE;
    }

    http_hello_page(request, response);

    fclose(request);
    return EXIT_SUCCESS;
}