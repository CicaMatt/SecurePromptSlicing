#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 100
#define RESPONSE_BUFFER_SIZE 4096

void handle_request(FILE *input, FILE *output) {
    char username[MAX_USERNAME_LENGTH];
    char outputbuf[RESPONSE_BUFFER_SIZE];

    if (fgets(username, sizeof(username), input) != NULL) {
        // Remove newline character from the username if present
        size_t len = strlen(username);
        if (len > 0 && username[len - 1] == '\n') {
            username[len - 1] = '\0';
        }

        snprintf(outputbuf, sizeof(outputbuf),
                 "<html><body><h1>Hello, %s!</h1></body></html>", username);

        fprintf(output, "%s", outputbuf);
    }

    fclose(output);
}

int main() {
    FILE *input = stdin;
    FILE *output = stdout;

    handle_request(input, output);

    return 0;
}