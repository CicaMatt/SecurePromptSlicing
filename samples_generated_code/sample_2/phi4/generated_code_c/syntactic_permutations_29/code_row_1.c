#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 2048

int main() {
    char input[MAX_URL_LENGTH];

    printf("Enter the target URL: ");
    if (fgets(input, sizeof(input), stdin) != NULL) {
        // Remove newline character from fgets
        size_t len = strlen(input);
        if (len > 0 && input[len - 1] == '\n') {
            input[--len] = '\0';
        }

        // Check if the target matches example.com
        char *redirect_url = "/";
        if (strstr(input, "example.com") != NULL) {
            redirect_url = input;
        }

        printf("Redirecting to: %s\n", redirect_url);
    } else {
        fprintf(stderr, "Error reading input.\n");
    }

    return 0;
}