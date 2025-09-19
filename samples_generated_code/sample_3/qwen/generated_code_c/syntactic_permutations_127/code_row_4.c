#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    const char *username = NULL;

    while (fgets(buffer, sizeof(buffer), request) != NULL) {
        if (strstr(buffer, "username=") == buffer) {
            username = buffer + strlen("username=");
            char *newline = strchr(username, '\n');
            if (newline) {
                *newline = '\0';
            }
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