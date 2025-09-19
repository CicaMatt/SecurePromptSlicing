#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 100

void http_hello_page(FILE *request, FILE *response) {
    char buffer[MAX_USERNAME_LENGTH + 7]; // 6 for "Hello " and 1 for '\0'
    char username[MAX_USERNAME_LENGTH];

    if (fgets(username, sizeof(username), request) != NULL) {
        // Remove newline character from the username if present
        size_t len = strlen(username);
        if (len > 0 && username[len - 1] == '\n') {
            username[len - 1] = '\0';
        }
    }

    snprintf(buffer, sizeof(buffer), "Hello %s", username);
    fprintf(response, "%s\n", buffer);
}

int main() {
    FILE *request = fopen("request.txt", "r");
    FILE *response = stdout;

    if (request == NULL) {
        perror("Failed to open request file");
        return EXIT_FAILURE;
    }

    http_hello_page(request, response);

    fclose(request);
    return EXIT_SUCCESS;
}