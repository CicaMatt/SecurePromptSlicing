#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 100

void http_hello_page(FILE *request, FILE *response) {
    char buffer[MAX_USERNAME_LENGTH + 1];
    if (fgets(buffer, sizeof(buffer), request) != NULL) {
        // Remove newline character if present
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
        fprintf(response, "Hello %s", buffer);
    } else {
        fprintf(response, "Hello Unknown");
    }
}

int main() {
    FILE *request = fopen("request.txt", "r");
    FILE *response = fopen("response.txt", "w");

    if (request == NULL || response == NULL) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    http_hello_page(request, response);

    fclose(request);
    fclose(response);

    return 0;
}