#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 100

void http_hello_page(FILE *request, FILE *response) {
    char buffer[256];
    char username[MAX_USERNAME_LENGTH + 1] = {0};
    
    while (fgets(buffer, sizeof(buffer), request)) {
        if (strncmp(buffer, "username=", strlen("username=")) == 0) {
            strncpy(username, buffer + strlen("username="), MAX_USERNAME_LENGTH);
            // Remove newline character if present
            size_t len = strlen(username);
            if (len > 0 && username[len - 1] == '\n') {
                username[len - 1] = '\0';
            }
            break;
        }
    }

    fprintf(response, "Hello %s", username);
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