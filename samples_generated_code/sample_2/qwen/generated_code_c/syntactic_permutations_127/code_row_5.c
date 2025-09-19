#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    const char *user_prefix = "username=";
    char username[100] = {0};

    while (fgets(buffer, sizeof(buffer), request)) {
        if (strstr(buffer, user_prefix)) {
            strncpy(username, strstr(buffer, user_prefix) + strlen(user_prefix), sizeof(username) - 1);
            // Remove newline character if present
            username[strcspn(username, "\r\n")] = '\0';
            break;
        }
    }

    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/plain\r\n");
    fprintf(response, "\r\n");
    fprintf(response, "Hello %s", username);
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