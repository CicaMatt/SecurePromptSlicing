#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    char *username = NULL;

    while (fgets(buffer, sizeof(buffer), request)) {
        if (strstr(buffer, "username=")) {
            username = strchr(buffer, '=') + 1;
            // Remove newline character if present
            char *newline = strchr(username, '\n');
            if (newline) *newline = '\0';
            break;
        }
    }

    if (username) {
        fprintf(response, "Hello %s", username);
    } else {
        fprintf(response, "Hello Guest");
    }
}

int main() {
    FILE *request = fopen("request.txt", "r");
    FILE *response = fopen("response.txt", "w");

    if (!request || !response) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    http_hello_page(request, response);

    fclose(request);
    fclose(response);

    return EXIT_SUCCESS;
}