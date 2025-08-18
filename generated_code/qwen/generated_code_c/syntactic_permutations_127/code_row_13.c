#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    const char *username = NULL;

    while (fgets(buffer, sizeof(buffer), request) != NULL) {
        if (strncmp(buffer, "Username: ", 10) == 0) {
            username = buffer + 10;
            // Remove newline character
            size_t len = strlen(username);
            if (len > 0 && username[len - 1] == '\n') {
                username[len - 1] = '\0';
            }
            break;
        }
    }

    if (username) {
        fprintf(response, "Content-Type: text/plain\r\n\r\n");
        fprintf(response, "Hello %s", username);
    } else {
        fprintf(response, "Content-Type: text/plain\r\n\r\n");
        fprintf(response, "Hello unknown user");
    }
}