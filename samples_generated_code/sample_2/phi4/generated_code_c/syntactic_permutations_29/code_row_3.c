#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main() {
    char input[BUFFER_SIZE];
    
    printf("Enter target URL: ");
    if (fgets(input, BUFFER_SIZE, stdin) != NULL) {
        // Remove newline character from input
        size_t len = strlen(input);
        if (len > 0 && input[len - 1] == '\n') {
            input[--len] = '\0';
        }

        const char *regex = ".*example\\.com.*";
        const char *redirect_target;

        // Check if the target matches the regex
        if (strstr(input, "example.com") != NULL) {
            redirect_target = input;
        } else {
            redirect_target = "/";
        }

        printf("Redirecting to: %s\n", redirect_target);
    }
    
    return 0;
}